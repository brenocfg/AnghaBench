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
struct octeon_irq_gpio_domain_data {int /*<<< orphan*/  base_hwirq; } ;
struct irq_domain {struct octeon_irq_gpio_domain_data* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__**) ; 
 int EINVAL ; 
 int /*<<< orphan*/  handle_level_irq ; 
 scalar_t__** octeon_irq_ciu_to_irq ; 
 int /*<<< orphan*/  octeon_irq_gpio_chip ; 
 int octeon_irq_set_ciu_mapping (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int octeon_irq_gpio_map(struct irq_domain *d,
			       unsigned int virq, irq_hw_number_t hw)
{
	struct octeon_irq_gpio_domain_data *gpiod = d->host_data;
	unsigned int line, bit;
	int r;

	line = (hw + gpiod->base_hwirq) >> 6;
	bit = (hw + gpiod->base_hwirq) & 63;
	if (line >= ARRAY_SIZE(octeon_irq_ciu_to_irq) ||
		octeon_irq_ciu_to_irq[line][bit] != 0)
		return -EINVAL;

	/*
	 * Default to handle_level_irq. If the DT contains a different
	 * trigger type, it will call the irq_set_type callback and
	 * the handler gets updated.
	 */
	r = octeon_irq_set_ciu_mapping(virq, line, bit, hw,
				       octeon_irq_gpio_chip, handle_level_irq);
	return r;
}