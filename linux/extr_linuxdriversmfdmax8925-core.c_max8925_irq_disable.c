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
struct max8925_chip {size_t irq_base; } ;
struct irq_data {size_t irq; } ;
struct TYPE_2__ {scalar_t__ enable; } ;

/* Variables and functions */
 struct max8925_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 TYPE_1__* max8925_irqs ; 

__attribute__((used)) static void max8925_irq_disable(struct irq_data *data)
{
	struct max8925_chip *chip = irq_data_get_irq_chip_data(data);

	max8925_irqs[data->irq - chip->irq_base].enable = 0;
}