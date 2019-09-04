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
struct ts4800_irq_data {int /*<<< orphan*/  irq_chip; } ;
struct irq_domain {struct ts4800_irq_data* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct ts4800_irq_data*) ; 
 int /*<<< orphan*/  irq_set_noprobe (unsigned int) ; 

__attribute__((used)) static int ts4800_irqdomain_map(struct irq_domain *d, unsigned int irq,
				irq_hw_number_t hwirq)
{
	struct ts4800_irq_data *data = d->host_data;

	irq_set_chip_and_handler(irq, &data->irq_chip, handle_simple_irq);
	irq_set_chip_data(irq, data);
	irq_set_noprobe(irq);

	return 0;
}