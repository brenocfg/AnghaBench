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
struct ethtool_regs {int version; } ;
struct de_private {int de21040; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int DE_REGS_VER ; 
 int /*<<< orphan*/  __de_get_regs (struct de_private*,void*) ; 
 struct de_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void de_get_regs(struct net_device *dev, struct ethtool_regs *regs,
			void *data)
{
	struct de_private *de = netdev_priv(dev);

	regs->version = (DE_REGS_VER << 2) | de->de21040;

	spin_lock_irq(&de->lock);
	__de_get_regs(de, data);
	spin_unlock_irq(&de->lock);
}