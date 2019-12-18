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
struct pcf857x {int irq_enabled; } ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 struct pcf857x* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void pcf857x_irq_enable(struct irq_data *data)
{
	struct pcf857x *gpio = irq_data_get_irq_chip_data(data);

	gpio->irq_enabled |= (1 << data->hwirq);
}