#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {struct list_head* next; } ;
struct hw_fib {int dummy; } ;
struct aac_dev {int /*<<< orphan*/  fib_lock; struct list_head fib_list; TYPE_2__* init; } ;
struct TYPE_3__ {int /*<<< orphan*/  adapter_fibs_size; } ;
struct TYPE_4__ {TYPE_1__ r7; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int get_fib_count(struct aac_dev *dev)
{
	unsigned int num = 0;
	struct list_head *entry;
	unsigned long flagv;

	/*
	 * Warning: no sleep allowed while
	 * holding spinlock. We take the estimate
	 * and pre-allocate a set of fibs outside the
	 * lock.
	 */
	num = le32_to_cpu(dev->init->r7.adapter_fibs_size)
			/ sizeof(struct hw_fib); /* some extra */
	spin_lock_irqsave(&dev->fib_lock, flagv);
	entry = dev->fib_list.next;
	while (entry != &dev->fib_list) {
		entry = entry->next;
		++num;
	}
	spin_unlock_irqrestore(&dev->fib_lock, flagv);

	return num;
}