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
 int /*<<< orphan*/  AUX_IENABLE ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 unsigned int read_aux_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void nps400_irq_unmask(struct irq_data *irqd)
{
	unsigned int ienb;
	unsigned int irq = irqd_to_hwirq(irqd);

	ienb = read_aux_reg(AUX_IENABLE);
	ienb |= (1 << irq);
	write_aux_reg(AUX_IENABLE, ienb);
}