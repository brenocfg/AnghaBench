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
struct net_device {int dummy; } ;
struct ag71xx {int /*<<< orphan*/  restart_work; } ;

/* Variables and functions */
 struct ag71xx* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ag71xx*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static void ag71xx_tx_timeout(struct net_device *ndev)
{
	struct ag71xx *ag = netdev_priv(ndev);

	netif_err(ag, tx_err, ndev, "tx timeout\n");

	schedule_delayed_work(&ag->restart_work, 1);
}