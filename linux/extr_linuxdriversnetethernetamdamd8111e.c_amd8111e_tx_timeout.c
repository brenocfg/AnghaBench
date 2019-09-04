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
struct amd8111e_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int amd8111e_restart (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amd8111e_tx_timeout(struct net_device *dev)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	int err;

	netdev_err(dev, "transmit timed out, resetting\n");

	spin_lock_irq(&lp->lock);
	err = amd8111e_restart(dev);
	spin_unlock_irq(&lp->lock);
	if(!err)
		netif_wake_queue(dev);
}