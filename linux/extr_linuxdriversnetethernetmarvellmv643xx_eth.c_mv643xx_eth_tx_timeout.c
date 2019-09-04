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
struct mv643xx_eth_private {int /*<<< orphan*/  tx_timeout_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mv643xx_eth_tx_timeout(struct net_device *dev)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);

	netdev_info(dev, "tx timeout\n");

	schedule_work(&mp->tx_timeout_task);
}