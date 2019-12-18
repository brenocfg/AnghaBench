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
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  PDC_MAX_IRQS ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct irq_domain* irq_domain_create_hierarchy (struct irq_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct irq_domain* irq_find_host (struct device_node*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_base ; 
 int /*<<< orphan*/  pdc_region ; 
 int pdc_setup_pin_mapping (struct device_node*) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*) ; 
 int /*<<< orphan*/  qcom_pdc_ops ; 

__attribute__((used)) static int qcom_pdc_init(struct device_node *node, struct device_node *parent)
{
	struct irq_domain *parent_domain, *pdc_domain;
	int ret;

	pdc_base = of_iomap(node, 0);
	if (!pdc_base) {
		pr_err("%pOF: unable to map PDC registers\n", node);
		return -ENXIO;
	}

	parent_domain = irq_find_host(parent);
	if (!parent_domain) {
		pr_err("%pOF: unable to find PDC's parent domain\n", node);
		ret = -ENXIO;
		goto fail;
	}

	ret = pdc_setup_pin_mapping(node);
	if (ret) {
		pr_err("%pOF: failed to init PDC pin-hwirq mapping\n", node);
		goto fail;
	}

	pdc_domain = irq_domain_create_hierarchy(parent_domain, 0, PDC_MAX_IRQS,
						 of_fwnode_handle(node),
						 &qcom_pdc_ops, NULL);
	if (!pdc_domain) {
		pr_err("%pOF: GIC domain add failed\n", node);
		ret = -ENOMEM;
		goto fail;
	}

	return 0;

fail:
	kfree(pdc_region);
	iounmap(pdc_base);
	return ret;
}