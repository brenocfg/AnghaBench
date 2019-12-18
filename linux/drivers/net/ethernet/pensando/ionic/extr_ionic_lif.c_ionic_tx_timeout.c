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
struct ionic_lif {int /*<<< orphan*/  tx_timeout_work; } ;

/* Variables and functions */
 struct ionic_lif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ionic_tx_timeout(struct net_device *netdev)
{
	struct ionic_lif *lif = netdev_priv(netdev);

	schedule_work(&lif->tx_timeout_work);
}