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
struct mdp5_mdss {int dummy; } ;
struct irq_domain {struct mdp5_mdss* host_data; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int EPERM ; 
 int VALID_IRQS ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct mdp5_mdss*) ; 
 int /*<<< orphan*/  mdss_hw_irq_chip ; 

__attribute__((used)) static int mdss_hw_irqdomain_map(struct irq_domain *d, unsigned int irq,
				 irq_hw_number_t hwirq)
{
	struct mdp5_mdss *mdp5_mdss = d->host_data;

	if (!(VALID_IRQS & (1 << hwirq)))
		return -EPERM;

	irq_set_chip_and_handler(irq, &mdss_hw_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, mdp5_mdss);

	return 0;
}