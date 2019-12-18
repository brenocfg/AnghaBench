#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rza1_irqc_priv {TYPE_3__* map; TYPE_2__* dev; int /*<<< orphan*/  chip; } ;
struct irq_fwspec {unsigned int* param; unsigned int param_count; int /*<<< orphan*/ * fwnode; } ;
struct irq_domain {struct rza1_irqc_priv* host_data; } ;
struct TYPE_6__ {unsigned int args_count; unsigned int* args; } ;
struct TYPE_5__ {TYPE_1__* of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,unsigned int,struct irq_fwspec*) ; 
 int irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,unsigned int,int /*<<< orphan*/ *,struct rza1_irqc_priv*) ; 

__attribute__((used)) static int rza1_irqc_alloc(struct irq_domain *domain, unsigned int virq,
			   unsigned int nr_irqs, void *arg)
{
	struct rza1_irqc_priv *priv = domain->host_data;
	struct irq_fwspec *fwspec = arg;
	unsigned int hwirq = fwspec->param[0];
	struct irq_fwspec spec;
	unsigned int i;
	int ret;

	ret = irq_domain_set_hwirq_and_chip(domain, virq, hwirq, &priv->chip,
					    priv);
	if (ret)
		return ret;

	spec.fwnode = &priv->dev->of_node->fwnode;
	spec.param_count = priv->map[hwirq].args_count;
	for (i = 0; i < spec.param_count; i++)
		spec.param[i] = priv->map[hwirq].args[i];

	return irq_domain_alloc_irqs_parent(domain, virq, nr_irqs, &spec);
}