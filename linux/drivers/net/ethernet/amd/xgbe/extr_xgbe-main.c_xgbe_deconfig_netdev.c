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
struct TYPE_2__ {int /*<<< orphan*/  (* phy_exit ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {TYPE_1__ phy_if; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PTP_1588_CLOCK ; 
 scalar_t__ IS_REACHABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  xgbe_debugfs_exit (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_ptp_unregister (struct xgbe_prv_data*) ; 

void xgbe_deconfig_netdev(struct xgbe_prv_data *pdata)
{
	struct net_device *netdev = pdata->netdev;

	xgbe_debugfs_exit(pdata);

	if (IS_REACHABLE(CONFIG_PTP_1588_CLOCK))
		xgbe_ptp_unregister(pdata);

	unregister_netdev(netdev);

	pdata->phy_if.phy_exit(pdata);
}