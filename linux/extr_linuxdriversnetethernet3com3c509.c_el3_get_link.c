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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct el3_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  el3_link_ok (struct net_device*) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 el3_get_link(struct net_device *dev)
{
	struct el3_private *lp = netdev_priv(dev);
	u32 ret;

	spin_lock_irq(&lp->lock);
	ret = el3_link_ok(dev);
	spin_unlock_irq(&lp->lock);
	return ret;
}