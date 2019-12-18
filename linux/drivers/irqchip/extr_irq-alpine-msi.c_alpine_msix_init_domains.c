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
struct irq_domain {struct irq_domain* parent; } ;
struct device_node {int dummy; } ;
struct alpine_msix_data {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  alpine_msix_domain_info ; 
 int /*<<< orphan*/  alpine_msix_middle_domain_ops ; 
 struct irq_domain* irq_domain_add_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct alpine_msix_data*) ; 
 int /*<<< orphan*/  irq_domain_remove (struct irq_domain*) ; 
 struct irq_domain* irq_find_host (struct device_node*) ; 
 struct device_node* of_irq_find_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_to_fwnode (struct device_node*) ; 
 struct irq_domain* pci_msi_create_irq_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct irq_domain*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int alpine_msix_init_domains(struct alpine_msix_data *priv,
				    struct device_node *node)
{
	struct irq_domain *middle_domain, *msi_domain, *gic_domain;
	struct device_node *gic_node;

	gic_node = of_irq_find_parent(node);
	if (!gic_node) {
		pr_err("Failed to find the GIC node\n");
		return -ENODEV;
	}

	gic_domain = irq_find_host(gic_node);
	if (!gic_domain) {
		pr_err("Failed to find the GIC domain\n");
		return -ENXIO;
	}

	middle_domain = irq_domain_add_tree(NULL,
					    &alpine_msix_middle_domain_ops,
					    priv);
	if (!middle_domain) {
		pr_err("Failed to create the MSIX middle domain\n");
		return -ENOMEM;
	}

	middle_domain->parent = gic_domain;

	msi_domain = pci_msi_create_irq_domain(of_node_to_fwnode(node),
					       &alpine_msix_domain_info,
					       middle_domain);
	if (!msi_domain) {
		pr_err("Failed to create MSI domain\n");
		irq_domain_remove(middle_domain);
		return -ENOMEM;
	}

	return 0;
}