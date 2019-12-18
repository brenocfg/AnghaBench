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

/* Variables and functions */
 int /*<<< orphan*/  ltq_etop_hw_exit (struct net_device*) ; 
 int ltq_etop_hw_init (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void
ltq_etop_tx_timeout(struct net_device *dev)
{
	int err;

	ltq_etop_hw_exit(dev);
	err = ltq_etop_hw_init(dev);
	if (err)
		goto err_hw;
	netif_trans_update(dev);
	netif_wake_queue(dev);
	return;

err_hw:
	ltq_etop_hw_exit(dev);
	netdev_err(dev, "failed to restart etop after TX timeout\n");
}