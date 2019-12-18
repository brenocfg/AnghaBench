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
struct irq_domain {int /*<<< orphan*/  fwnode; struct irq_domain* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_BUS_NEXUS ; 
 int ENOMEM ; 
 struct irq_domain* irq_domain_create_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_remove (struct irq_domain*) ; 
 int /*<<< orphan*/  irq_domain_update_bus_token (struct irq_domain*,int /*<<< orphan*/ ) ; 
 int mbi_allocate_pci_domain (struct irq_domain*,struct irq_domain**) ; 
 int /*<<< orphan*/  mbi_domain_ops ; 
 int /*<<< orphan*/  mbi_pmsi_domain_info ; 
 struct irq_domain* platform_msi_create_irq_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct irq_domain*) ; 

__attribute__((used)) static int mbi_allocate_domains(struct irq_domain *parent)
{
	struct irq_domain *nexus_domain, *pci_domain, *plat_domain;
	int err;

	nexus_domain = irq_domain_create_tree(parent->fwnode,
					      &mbi_domain_ops, NULL);
	if (!nexus_domain)
		return -ENOMEM;

	irq_domain_update_bus_token(nexus_domain, DOMAIN_BUS_NEXUS);
	nexus_domain->parent = parent;

	err = mbi_allocate_pci_domain(nexus_domain, &pci_domain);

	plat_domain = platform_msi_create_irq_domain(parent->fwnode,
						     &mbi_pmsi_domain_info,
						     nexus_domain);

	if (err || !plat_domain) {
		if (plat_domain)
			irq_domain_remove(plat_domain);
		if (pci_domain)
			irq_domain_remove(pci_domain);
		irq_domain_remove(nexus_domain);
		return -ENOMEM;
	}

	return 0;
}