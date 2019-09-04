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
struct netdev_private {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  NATSEMI_REGS_VER ; 
 int /*<<< orphan*/  netdev_get_regs (struct net_device*,void*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_regs(struct net_device *dev, struct ethtool_regs *regs, void *buf)
{
	struct netdev_private *np = netdev_priv(dev);
	regs->version = NATSEMI_REGS_VER;
	spin_lock_irq(&np->lock);
	netdev_get_regs(dev, buf);
	spin_unlock_irq(&np->lock);
}