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
struct kfd_dev {int interrupts_active; int /*<<< orphan*/  ih_fifo; int /*<<< orphan*/  ih_wq; int /*<<< orphan*/  interrupt_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void kfd_interrupt_exit(struct kfd_dev *kfd)
{
	/*
	 * Stop the interrupt handler from writing to the ring and scheduling
	 * workqueue items. The spinlock ensures that any interrupt running
	 * after we have unlocked sees interrupts_active = false.
	 */
	unsigned long flags;

	spin_lock_irqsave(&kfd->interrupt_lock, flags);
	kfd->interrupts_active = false;
	spin_unlock_irqrestore(&kfd->interrupt_lock, flags);

	/*
	 * flush_work ensures that there are no outstanding
	 * work-queue items that will access interrupt_ring. New work items
	 * can't be created because we stopped interrupt handling above.
	 */
	flush_workqueue(kfd->ih_wq);

	kfifo_free(&kfd->ih_fifo);
}