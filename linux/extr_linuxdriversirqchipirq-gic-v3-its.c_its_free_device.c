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
struct its_device {struct its_device* itt; TYPE_1__* its; int /*<<< orphan*/  entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct its_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void its_free_device(struct its_device *its_dev)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&its_dev->its->lock, flags);
	list_del(&its_dev->entry);
	raw_spin_unlock_irqrestore(&its_dev->its->lock, flags);
	kfree(its_dev->itt);
	kfree(its_dev);
}