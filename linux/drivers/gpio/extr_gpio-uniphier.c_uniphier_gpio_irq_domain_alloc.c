#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uniphier_gpio_priv {int /*<<< orphan*/  irq_chip; } ;
struct irq_fwspec {int param_count; int* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* parent; struct uniphier_gpio_priv* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 scalar_t__ WARN_ON (int) ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,int,struct irq_fwspec*) ; 
 int irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct uniphier_gpio_priv*) ; 
 int uniphier_gpio_irq_domain_translate (struct irq_domain*,void*,int /*<<< orphan*/ *,unsigned int*) ; 
 int uniphier_gpio_irq_get_parent_hwirq (struct uniphier_gpio_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_gpio_irq_domain_alloc(struct irq_domain *domain,
					  unsigned int virq,
					  unsigned int nr_irqs, void *arg)
{
	struct uniphier_gpio_priv *priv = domain->host_data;
	struct irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;
	unsigned int type;
	int ret;

	if (WARN_ON(nr_irqs != 1))
		return -EINVAL;

	ret = uniphier_gpio_irq_domain_translate(domain, arg, &hwirq, &type);
	if (ret)
		return ret;

	ret = uniphier_gpio_irq_get_parent_hwirq(priv, hwirq);
	if (ret < 0)
		return ret;

	/* parent is UniPhier AIDET */
	parent_fwspec.fwnode = domain->parent->fwnode;
	parent_fwspec.param_count = 2;
	parent_fwspec.param[0] = ret;
	parent_fwspec.param[1] = (type == IRQ_TYPE_EDGE_BOTH) ?
						IRQ_TYPE_EDGE_FALLING : type;

	ret = irq_domain_set_hwirq_and_chip(domain, virq, hwirq,
					    &priv->irq_chip, priv);
	if (ret)
		return ret;

	return irq_domain_alloc_irqs_parent(domain, virq, 1, &parent_fwspec);
}