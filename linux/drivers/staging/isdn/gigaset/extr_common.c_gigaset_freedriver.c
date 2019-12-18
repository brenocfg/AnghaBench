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
struct gigaset_driver {struct gigaset_driver* cs; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_lock ; 
 int /*<<< orphan*/  gigaset_if_freedriver (struct gigaset_driver*) ; 
 int /*<<< orphan*/  kfree (struct gigaset_driver*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void gigaset_freedriver(struct gigaset_driver *drv)
{
	unsigned long flags;

	spin_lock_irqsave(&driver_lock, flags);
	list_del(&drv->list);
	spin_unlock_irqrestore(&driver_lock, flags);

	gigaset_if_freedriver(drv);

	kfree(drv->cs);
	kfree(drv);
}