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
struct xgbe_prv_data {int /*<<< orphan*/  restart_work; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgbe_tx_timeout(struct net_device *netdev)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);

	netdev_warn(netdev, "tx timeout, device restarting\n");
	schedule_work(&pdata->restart_work);
}