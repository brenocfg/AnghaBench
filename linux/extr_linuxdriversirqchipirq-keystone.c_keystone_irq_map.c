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
struct keystone_irq_device {int /*<<< orphan*/  chip; } ;
struct irq_domain {struct keystone_irq_device* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct keystone_irq_device*) ; 
 int /*<<< orphan*/  irq_set_probe (unsigned int) ; 

__attribute__((used)) static int keystone_irq_map(struct irq_domain *h, unsigned int virq,
				irq_hw_number_t hw)
{
	struct keystone_irq_device *kirq = h->host_data;

	irq_set_chip_data(virq, kirq);
	irq_set_chip_and_handler(virq, &kirq->chip, handle_level_irq);
	irq_set_probe(virq);
	return 0;
}