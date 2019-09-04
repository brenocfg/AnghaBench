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
struct mx25_tsadc {int dummy; } ;
struct irq_domain {struct mx25_tsadc* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NOPROBE ; 
 int /*<<< orphan*/  IRQ_NOREQUEST ; 
 int /*<<< orphan*/  dummy_irq_chip ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_modify_status (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct mx25_tsadc*) ; 

__attribute__((used)) static int mx25_tsadc_domain_map(struct irq_domain *d, unsigned int irq,
				 irq_hw_number_t hwirq)
{
	struct mx25_tsadc *tsadc = d->host_data;

	irq_set_chip_data(irq, tsadc);
	irq_set_chip_and_handler(irq, &dummy_irq_chip,
				 handle_level_irq);
	irq_modify_status(irq, IRQ_NOREQUEST, IRQ_NOPROBE);

	return 0;
}