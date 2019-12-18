#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u8 ;
struct wil6210_vif {scalar_t__ mid; int /*<<< orphan*/  enable_tx_key_worker; int /*<<< orphan*/  probe_client_worker; int /*<<< orphan*/  disconnect_worker; int /*<<< orphan*/  connect_timer; } ;
struct wil6210_priv {int /*<<< orphan*/  wmi_event_worker; int /*<<< orphan*/  vif_mutex; int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  napi_rx; int /*<<< orphan*/  status; struct wil6210_vif** vifs; int /*<<< orphan*/  mutex; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 size_t GET_MAX_VIFS (struct wil6210_priv*) ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 
 struct net_device* vif_to_ndev (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil6210_disconnect (struct wil6210_vif*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,size_t) ; 
 int wil_has_active_ifaces (struct wil6210_priv*,int,int) ; 
 int /*<<< orphan*/  wil_probe_client_flush (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_status_napi_en ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  wmi_port_delete (struct wil6210_priv*,scalar_t__) ; 

void wil_vif_remove(struct wil6210_priv *wil, u8 mid)
{
	struct wil6210_vif *vif;
	struct net_device *ndev;
	bool any_active = wil_has_active_ifaces(wil, true, false);

	ASSERT_RTNL();
	if (mid >= GET_MAX_VIFS(wil)) {
		wil_err(wil, "invalid MID: %d\n", mid);
		return;
	}

	vif = wil->vifs[mid];
	if (!vif) {
		wil_err(wil, "MID %d not registered\n", mid);
		return;
	}

	mutex_lock(&wil->mutex);
	wil6210_disconnect(vif, NULL, WLAN_REASON_DEAUTH_LEAVING);
	mutex_unlock(&wil->mutex);

	ndev = vif_to_ndev(vif);
	/* during unregister_netdevice cfg80211_leave may perform operations
	 * such as stop AP, disconnect, so we only clear the VIF afterwards
	 */
	unregister_netdevice(ndev);

	if (any_active && vif->mid != 0)
		wmi_port_delete(wil, vif->mid);

	/* make sure no one is accessing the VIF before removing */
	mutex_lock(&wil->vif_mutex);
	wil->vifs[mid] = NULL;
	/* ensure NAPI code will see the NULL VIF */
	wmb();
	if (test_bit(wil_status_napi_en, wil->status)) {
		napi_synchronize(&wil->napi_rx);
		napi_synchronize(&wil->napi_tx);
	}
	mutex_unlock(&wil->vif_mutex);

	flush_work(&wil->wmi_event_worker);
	del_timer_sync(&vif->connect_timer);
	cancel_work_sync(&vif->disconnect_worker);
	wil_probe_client_flush(vif);
	cancel_work_sync(&vif->probe_client_worker);
	cancel_work_sync(&vif->enable_tx_key_worker);
	/* for VIFs, ndev will be freed by destructor after RTNL is unlocked.
	 * the main interface will be freed in wil_if_free, we need to keep it
	 * a bit longer so logging macros will work.
	 */
}