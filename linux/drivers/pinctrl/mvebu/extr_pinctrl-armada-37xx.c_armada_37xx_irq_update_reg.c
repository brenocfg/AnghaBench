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
 int /*<<< orphan*/  armada_37xx_update_reg (unsigned int*,int*) ; 
 int irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static inline void armada_37xx_irq_update_reg(unsigned int *reg,
					  struct irq_data *d)
{
	int offset = irqd_to_hwirq(d);

	armada_37xx_update_reg(reg, &offset);
}