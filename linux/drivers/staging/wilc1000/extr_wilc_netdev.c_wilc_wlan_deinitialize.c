#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {int initialized; int /*<<< orphan*/  txq_event; int /*<<< orphan*/  hif_cs; TYPE_1__* hif_func; int /*<<< orphan*/  dev_irq_num; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_interrupt ) (struct wilc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deinit_irq (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct wilc*) ; 
 int /*<<< orphan*/  wilc_wlan_cleanup (struct net_device*) ; 
 int /*<<< orphan*/  wilc_wlan_stop (struct wilc*,struct wilc_vif*) ; 
 int /*<<< orphan*/  wlan_deinit_locks (struct net_device*) ; 
 int /*<<< orphan*/  wlan_deinitialize_threads (struct net_device*) ; 

__attribute__((used)) static void wilc_wlan_deinitialize(struct net_device *dev)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wl = vif->wilc;

	if (!wl) {
		netdev_err(dev, "wl is NULL\n");
		return;
	}

	if (wl->initialized) {
		netdev_info(dev, "Deinitializing wilc1000...\n");

		if (!wl->dev_irq_num &&
		    wl->hif_func->disable_interrupt) {
			mutex_lock(&wl->hif_cs);
			wl->hif_func->disable_interrupt(wl);
			mutex_unlock(&wl->hif_cs);
		}
		complete(&wl->txq_event);

		wlan_deinitialize_threads(dev);
		deinit_irq(dev);

		wilc_wlan_stop(wl, vif);
		wilc_wlan_cleanup(dev);
		wlan_deinit_locks(dev);

		wl->initialized = false;

		netdev_dbg(dev, "wilc1000 deinitialization Done\n");
	} else {
		netdev_dbg(dev, "wilc1000 is not initialized\n");
	}
}