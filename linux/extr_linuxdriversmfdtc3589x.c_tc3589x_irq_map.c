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
struct tc3589x {int dummy; } ;
struct irq_domain {struct tc3589x* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  dummy_irq_chip ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct tc3589x*) ; 
 int /*<<< orphan*/  irq_set_nested_thread (unsigned int,int) ; 
 int /*<<< orphan*/  irq_set_noprobe (unsigned int) ; 

__attribute__((used)) static int tc3589x_irq_map(struct irq_domain *d, unsigned int virq,
				irq_hw_number_t hwirq)
{
	struct tc3589x *tc3589x = d->host_data;

	irq_set_chip_data(virq, tc3589x);
	irq_set_chip_and_handler(virq, &dummy_irq_chip,
				handle_edge_irq);
	irq_set_nested_thread(virq, 1);
	irq_set_noprobe(virq);

	return 0;
}