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
struct net_device {int dummy; } ;
struct fs_enet_private {int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct ethtool_regs {int len; scalar_t__ version; } ;
struct TYPE_2__ {int (* get_regs ) (struct net_device*,void*,int*) ;} ;

/* Variables and functions */
 struct fs_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct net_device*,void*,int*) ; 

__attribute__((used)) static void fs_get_regs(struct net_device *dev, struct ethtool_regs *regs,
			 void *p)
{
	struct fs_enet_private *fep = netdev_priv(dev);
	unsigned long flags;
	int r, len;

	len = regs->len;

	spin_lock_irqsave(&fep->lock, flags);
	r = (*fep->ops->get_regs)(dev, p, &len);
	spin_unlock_irqrestore(&fep->lock, flags);

	if (r == 0)
		regs->version = 0;
}