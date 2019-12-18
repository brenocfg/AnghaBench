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
struct mlxbf_tmfifo_irq_info {TYPE_1__* fifo; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  pend_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mlxbf_tmfifo_irq_handler(int irq, void *arg)
{
	struct mlxbf_tmfifo_irq_info *irq_info = arg;

	if (!test_and_set_bit(irq_info->index, &irq_info->fifo->pend_events))
		schedule_work(&irq_info->fifo->work);

	return IRQ_HANDLED;
}