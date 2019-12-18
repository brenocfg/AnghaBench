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
struct sih_agent {int imr_change_pending; scalar_t__ irq_base; int /*<<< orphan*/  imr; } ;
struct irq_data {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 struct sih_agent* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void twl4030_sih_mask(struct irq_data *data)
{
	struct sih_agent *agent = irq_data_get_irq_chip_data(data);

	agent->imr |= BIT(data->irq - agent->irq_base);
	agent->imr_change_pending = true;
}