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
struct irq_domain {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_probe (unsigned int) ; 
 int /*<<< orphan*/  sun4i_irq_chip ; 

__attribute__((used)) static int sun4i_irq_map(struct irq_domain *d, unsigned int virq,
			 irq_hw_number_t hw)
{
	irq_set_chip_and_handler(virq, &sun4i_irq_chip, handle_fasteoi_irq);
	irq_set_probe(virq);

	return 0;
}