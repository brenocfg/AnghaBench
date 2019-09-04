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
struct stm32_exti_host_data {int /*<<< orphan*/  drv_data; struct stm32_exti_chip_data* chips_data; } ;
struct stm32_exti_chip_data {int dummy; } ;
struct irq_fwspec {int* param; int param_count; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* parent; struct stm32_exti_host_data* host_data; } ;
typedef  int irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int GIC_SPI ; 
 int IRQS_PER_BANK ; 
 int IRQ_TYPE_LEVEL_HIGH ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,int,struct irq_fwspec*) ; 
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,int,int /*<<< orphan*/ *,struct stm32_exti_chip_data*) ; 
 int /*<<< orphan*/  stm32_exti_h_chip ; 
 int stm32_exti_to_irq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32_exti_h_domain_alloc(struct irq_domain *dm,
				     unsigned int virq,
				     unsigned int nr_irqs, void *data)
{
	struct stm32_exti_host_data *host_data = dm->host_data;
	struct stm32_exti_chip_data *chip_data;
	struct irq_fwspec *fwspec = data;
	struct irq_fwspec p_fwspec;
	irq_hw_number_t hwirq;
	int p_irq, bank;

	hwirq = fwspec->param[0];
	bank  = hwirq / IRQS_PER_BANK;
	chip_data = &host_data->chips_data[bank];

	irq_domain_set_hwirq_and_chip(dm, virq, hwirq,
				      &stm32_exti_h_chip, chip_data);

	p_irq = stm32_exti_to_irq(host_data->drv_data, hwirq);
	if (p_irq >= 0) {
		p_fwspec.fwnode = dm->parent->fwnode;
		p_fwspec.param_count = 3;
		p_fwspec.param[0] = GIC_SPI;
		p_fwspec.param[1] = p_irq;
		p_fwspec.param[2] = IRQ_TYPE_LEVEL_HIGH;

		return irq_domain_alloc_irqs_parent(dm, virq, 1, &p_fwspec);
	}

	return 0;
}