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
struct genwqe_dev {int /*<<< orphan*/  queue_waitq; int /*<<< orphan*/  irqs_processed; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t genwqe_vf_isr(int irq, void *dev_id)
{
	struct genwqe_dev *cd = (struct genwqe_dev *)dev_id;

	cd->irqs_processed++;
	wake_up_interruptible(&cd->queue_waitq);

	return IRQ_HANDLED;
}