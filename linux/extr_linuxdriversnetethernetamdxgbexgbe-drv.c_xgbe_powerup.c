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
struct xgbe_hw_if {int /*<<< orphan*/  (* powerup_rx ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* powerup_tx ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/  lock; scalar_t__ power_down; struct xgbe_hw_if hw_if; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int EINVAL ; 
 unsigned int XGMAC_DRIVER_CONTEXT ; 
 unsigned int XGMAC_IOCTL_CONTEXT ; 
 int /*<<< orphan*/  netdev_alert (struct net_device*,char*) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_napi_enable (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_start_timers (struct xgbe_prv_data*) ; 

int xgbe_powerup(struct net_device *netdev, unsigned int caller)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	unsigned long flags;

	DBGPR("-->xgbe_powerup\n");

	if (!netif_running(netdev) ||
	    (caller == XGMAC_IOCTL_CONTEXT && !pdata->power_down)) {
		netdev_alert(netdev, "Device is already powered up\n");
		DBGPR("<--xgbe_powerup\n");
		return -EINVAL;
	}

	spin_lock_irqsave(&pdata->lock, flags);

	pdata->power_down = 0;

	xgbe_napi_enable(pdata, 0);

	hw_if->powerup_tx(pdata);
	hw_if->powerup_rx(pdata);

	if (caller == XGMAC_DRIVER_CONTEXT)
		netif_device_attach(netdev);

	netif_tx_start_all_queues(netdev);

	xgbe_start_timers(pdata);

	spin_unlock_irqrestore(&pdata->lock, flags);

	DBGPR("<--xgbe_powerup\n");

	return 0;
}