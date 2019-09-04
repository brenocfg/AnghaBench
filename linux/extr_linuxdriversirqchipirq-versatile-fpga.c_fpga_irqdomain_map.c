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
struct irq_domain {struct fpga_irq_data* host_data; } ;
struct fpga_irq_data {int valid; int /*<<< orphan*/  chip; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EPERM ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct fpga_irq_data*) ; 
 int /*<<< orphan*/  irq_set_probe (unsigned int) ; 

__attribute__((used)) static int fpga_irqdomain_map(struct irq_domain *d, unsigned int irq,
		irq_hw_number_t hwirq)
{
	struct fpga_irq_data *f = d->host_data;

	/* Skip invalid IRQs, only register handlers for the real ones */
	if (!(f->valid & BIT(hwirq)))
		return -EPERM;
	irq_set_chip_data(irq, f);
	irq_set_chip_and_handler(irq, &f->chip,
				handle_level_irq);
	irq_set_probe(irq);
	return 0;
}