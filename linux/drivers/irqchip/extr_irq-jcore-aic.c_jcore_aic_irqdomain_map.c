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
struct irq_domain {struct irq_chip* host_data; } ;
struct irq_chip {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_jcore_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,struct irq_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jcore_aic_irqdomain_map(struct irq_domain *d, unsigned int irq,
				   irq_hw_number_t hwirq)
{
	struct irq_chip *aic = d->host_data;

	irq_set_chip_and_handler(irq, aic, handle_jcore_irq);

	return 0;
}