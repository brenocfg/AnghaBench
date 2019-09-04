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
struct ehea_adapter {int /*<<< orphan*/  neq_tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ehea_interrupt_neq(int irq, void *param)
{
	struct ehea_adapter *adapter = param;
	tasklet_hi_schedule(&adapter->neq_tasklet);
	return IRQ_HANDLED;
}