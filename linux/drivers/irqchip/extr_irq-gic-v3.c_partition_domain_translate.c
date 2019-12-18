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
struct irq_fwspec {size_t* param; } ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ppi_descs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_1__ gic_data ; 
 struct device_node* of_find_node_by_phandle (size_t) ; 
 int /*<<< orphan*/  of_node_to_fwnode (struct device_node*) ; 
 int partition_translate_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int partition_domain_translate(struct irq_domain *d,
				      struct irq_fwspec *fwspec,
				      unsigned long *hwirq,
				      unsigned int *type)
{
	struct device_node *np;
	int ret;

	if (!gic_data.ppi_descs)
		return -ENOMEM;

	np = of_find_node_by_phandle(fwspec->param[3]);
	if (WARN_ON(!np))
		return -EINVAL;

	ret = partition_translate_id(gic_data.ppi_descs[fwspec->param[1]],
				     of_node_to_fwnode(np));
	if (ret < 0)
		return ret;

	*hwirq = ret;
	*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;

	return 0;
}