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
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {scalar_t__ connect_status; int /*<<< orphan*/  dev; scalar_t__ scan_req; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  driver_lock; } ;

/* Variables and functions */
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_disconnect (struct lbs_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_iface_active (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_scan_done (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_stop_iface (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_update_mcast (struct lbs_private*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_eth_stop(struct net_device *dev)
{
	struct lbs_private *priv = dev->ml_priv;

	if (priv->connect_status == LBS_CONNECTED)
		lbs_disconnect(priv, WLAN_REASON_DEAUTH_LEAVING);

	spin_lock_irq(&priv->driver_lock);
	netif_stop_queue(dev);
	spin_unlock_irq(&priv->driver_lock);

	lbs_update_mcast(priv);
	cancel_delayed_work_sync(&priv->scan_work);
	if (priv->scan_req)
		lbs_scan_done(priv);

	netif_carrier_off(priv->dev);

	if (!lbs_iface_active(priv))
		lbs_stop_iface(priv);

	return 0;
}