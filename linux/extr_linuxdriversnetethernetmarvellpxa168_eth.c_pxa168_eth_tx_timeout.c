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
struct pxa168_eth_private {int /*<<< orphan*/  tx_timeout_task; int /*<<< orphan*/  tx_desc_count; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pxa168_eth_tx_timeout(struct net_device *dev)
{
	struct pxa168_eth_private *pep = netdev_priv(dev);

	netdev_info(dev, "TX timeout  desc_count %d\n", pep->tx_desc_count);

	schedule_work(&pep->tx_timeout_task);
}