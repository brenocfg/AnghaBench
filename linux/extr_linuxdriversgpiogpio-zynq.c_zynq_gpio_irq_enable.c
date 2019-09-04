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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zynq_gpio_irq_ack (struct irq_data*) ; 
 int /*<<< orphan*/  zynq_gpio_irq_unmask (struct irq_data*) ; 

__attribute__((used)) static void zynq_gpio_irq_enable(struct irq_data *irq_data)
{
	/*
	 * The Zynq GPIO controller does not disable interrupt detection when
	 * the interrupt is masked and only disables the propagation of the
	 * interrupt. This means when the controller detects an interrupt
	 * condition while the interrupt is logically disabled it will propagate
	 * that interrupt event once the interrupt is enabled. This will cause
	 * the interrupt consumer to see spurious interrupts to prevent this
	 * first make sure that the interrupt is not asserted and then enable
	 * it.
	 */
	zynq_gpio_irq_ack(irq_data);
	zynq_gpio_irq_unmask(irq_data);
}