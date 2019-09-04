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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 

irq_hw_number_t virq_to_hw(unsigned int virq)
{
	struct irq_data *irq_data = irq_get_irq_data(virq);
	return WARN_ON(!irq_data) ? 0 : irq_data->hwirq;
}