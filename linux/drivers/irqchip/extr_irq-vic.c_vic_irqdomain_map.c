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
struct vic_device {int valid_sources; int /*<<< orphan*/  base; } ;
struct irq_domain {struct vic_device* host_data; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_probe (unsigned int) ; 
 int /*<<< orphan*/  vic_chip ; 

__attribute__((used)) static int vic_irqdomain_map(struct irq_domain *d, unsigned int irq,
			     irq_hw_number_t hwirq)
{
	struct vic_device *v = d->host_data;

	/* Skip invalid IRQs, only register handlers for the real ones */
	if (!(v->valid_sources & (1 << hwirq)))
		return -EPERM;
	irq_set_chip_and_handler(irq, &vic_chip, handle_level_irq);
	irq_set_chip_data(irq, v->base);
	irq_set_probe(irq);
	return 0;
}