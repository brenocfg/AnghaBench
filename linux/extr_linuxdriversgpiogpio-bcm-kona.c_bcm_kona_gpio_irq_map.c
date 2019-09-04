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
 int /*<<< orphan*/  bcm_gpio_irq_chip ; 
 int /*<<< orphan*/  gpio_lock_class ; 
 int /*<<< orphan*/  gpio_request_class ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int irq_set_chip_data (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_lockdep_class (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_noprobe (unsigned int) ; 

__attribute__((used)) static int bcm_kona_gpio_irq_map(struct irq_domain *d, unsigned int irq,
				 irq_hw_number_t hwirq)
{
	int ret;

	ret = irq_set_chip_data(irq, d->host_data);
	if (ret < 0)
		return ret;
	irq_set_lockdep_class(irq, &gpio_lock_class, &gpio_request_class);
	irq_set_chip_and_handler(irq, &bcm_gpio_irq_chip, handle_simple_irq);
	irq_set_noprobe(irq);

	return 0;
}