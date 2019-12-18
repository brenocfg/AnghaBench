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
struct r8192_priv {int /*<<< orphan*/  irq_rx_tasklet; int /*<<< orphan*/  qos_activate; int /*<<< orphan*/  initialgain_operate_wq; int /*<<< orphan*/  update_beacon_wq; int /*<<< orphan*/  rfpath_check_wq; int /*<<< orphan*/  txpower_tracking_wq; int /*<<< orphan*/  watch_dog_wq; int /*<<< orphan*/  reset_wq; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitialGainOperateWorkItemCallBack ; 
 int /*<<< orphan*/  dm_rf_pathcheck_workitemcallback ; 
 int /*<<< orphan*/  dm_txpower_trackingcallback ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ rtl8192_irq_rx_tasklet ; 
 int /*<<< orphan*/  rtl8192_qos_activate ; 
 int /*<<< orphan*/  rtl8192_restart ; 
 int /*<<< orphan*/  rtl8192_update_beacon ; 
 int /*<<< orphan*/  rtl819x_watchdog_wqcallback ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 

__attribute__((used)) static void rtl8192_init_priv_task(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);


	INIT_WORK(&priv->reset_wq, rtl8192_restart);

	INIT_DELAYED_WORK(&priv->watch_dog_wq,
			  rtl819x_watchdog_wqcallback);
	INIT_DELAYED_WORK(&priv->txpower_tracking_wq,
			  dm_txpower_trackingcallback);
	INIT_DELAYED_WORK(&priv->rfpath_check_wq,
			  dm_rf_pathcheck_workitemcallback);
	INIT_DELAYED_WORK(&priv->update_beacon_wq,
			  rtl8192_update_beacon);
	INIT_DELAYED_WORK(&priv->initialgain_operate_wq,
			  InitialGainOperateWorkItemCallBack);
	INIT_WORK(&priv->qos_activate, rtl8192_qos_activate);

	tasklet_init(&priv->irq_rx_tasklet,
		     (void(*)(unsigned long))rtl8192_irq_rx_tasklet,
		     (unsigned long)priv);
}