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
struct ei_device {int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_set_multicast_list (struct net_device*) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __ei_set_multicast_list(struct net_device *dev)
{
	unsigned long flags;
	struct ei_device *ei_local = netdev_priv(dev);

	spin_lock_irqsave(&ei_local->page_lock, flags);
	do_set_multicast_list(dev);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);
}