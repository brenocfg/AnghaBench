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
struct irq_domain {struct dpu_mdss* host_data; } ;
struct dpu_mdss {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_mdss_irq_chip ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int irq_set_chip_data (unsigned int,struct dpu_mdss*) ; 

__attribute__((used)) static int dpu_mdss_irqdomain_map(struct irq_domain *domain,
		unsigned int irq, irq_hw_number_t hwirq)
{
	struct dpu_mdss *dpu_mdss = domain->host_data;
	int ret;

	irq_set_chip_and_handler(irq, &dpu_mdss_irq_chip, handle_level_irq);
	ret = irq_set_chip_data(irq, dpu_mdss);

	return ret;
}