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
struct sc16is7xx_port {int /*<<< orphan*/  irq_work; int /*<<< orphan*/  kworker; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sc16is7xx_irq(int irq, void *dev_id)
{
	struct sc16is7xx_port *s = (struct sc16is7xx_port *)dev_id;

	kthread_queue_work(&s->kworker, &s->irq_work);

	return IRQ_HANDLED;
}