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
struct irq_domain {int /*<<< orphan*/  host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcm7038_l1_irq_chip ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_desc_get_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  irqd_set_single_target (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm7038_l1_map(struct irq_domain *d, unsigned int virq,
			  irq_hw_number_t hw_irq)
{
	irq_set_chip_and_handler(virq, &bcm7038_l1_irq_chip, handle_level_irq);
	irq_set_chip_data(virq, d->host_data);
	irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(virq)));
	return 0;
}