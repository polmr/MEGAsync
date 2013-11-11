#ifndef MEGAAPPLICATION_H
#define MEGAAPPLICATION_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QDir>
#include <QLocalServer>
#include <QLocalSocket>
#include <QDataStream>

#include "gui/InfoDialog.h"
#include "gui/SetupWizard.h"
#include "gui/SettingsDialog.h"
#include "utils/Preferences.h"
#include "utils/HTTPServer.h"
#include "utils/FileDownloader.h"
#include "sdk/megaapi.h"

class MegaApplication : public QApplication, public MegaListener
{
    Q_OBJECT

public:
    explicit MegaApplication(int &argc, char **argv);

    virtual void onRequestStart(MegaApi* api, MegaRequest *request);
    virtual void onRequestFinish(MegaApi* api, MegaRequest *request, MegaError* e);
    virtual void onRequestTemporaryError(MegaApi *api, MegaRequest *request, MegaError* e);
    virtual void onTransferFinish(MegaApi* api, MegaTransfer *transfer, MegaError* e);
    virtual void onTransferUpdate(MegaApi *api, MegaTransfer *transfer);
    virtual void onTransferTemporaryError(MegaApi *api, MegaTransfer *transfer, MegaError* e);
    virtual void onUsersUpdate(MegaApi* api, UserList *users);
    virtual void onNodesUpdate(MegaApi* api, NodeList *nodes);
    virtual void onReloadNeeded(MegaApi* api);

    MegaApi *getMegaApi() { return megaApi; }
    Preferences *getPreferences() { return preferences; }

    void showSyncedIcon();
    void showSyncingIcon();
    void unlink();

signals:

public slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void openSettings();
    void onNewLocalConnection();
    void onDataReady();
    void pauseSync();
    void resumeSync();
    void updateDowloaded();

protected:
    void createActions();
    void createTrayIcon();
    bool showTrayIconAlwaysNEW();
    void init();

    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *exitAction;
    QAction *settingsAction;
    QAction *pauseAction;
    QAction *resumeAction;
    SetupWizard *setupWizard;
    SettingsDialog *settingsDialog;
    InfoDialog *infoDialog;
    Preferences *preferences;
    MegaApi *megaApi;
    QLocalServer *localServer;
    HTTPServer *httpServer;
    FileDownloader *downloader;

private slots:
};

#endif // MEGAAPPLICATION_H
