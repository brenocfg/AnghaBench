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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct irq_domain* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct irq_domain* irq_find_host (struct device_node*) ; 
 int /*<<< orphan*/  of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_irq_find_parent (struct device_node*) ; 

__attribute__((used)) static struct irq_domain *stm32_pctrl_get_irq_domain(struct device_node *np)
{
	struct device_node *parent;
	struct irq_domain *domain;

	if (!of_find_property(np, "interrupt-parent", NULL))
		return NULL;

	parent = of_irq_find_parent(np);
	if (!parent)
		return ERR_PTR(-ENXIO);

	domain = irq_find_host(parent);
	if (!domain)
		/* domain not registered yet */
		return ERR_PTR(-EPROBE_DEFER);

	return domain;
}