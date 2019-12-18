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
struct resource {int start; int end; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct pci_bus {int /*<<< orphan*/  dev; TYPE_1__* parent; struct resource busn_res; } ;
struct TYPE_2__ {struct resource busn_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_BUS ; 
 int /*<<< orphan*/  IORESOURCE_PCI_FIXED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,struct resource*,char*,struct resource*,int /*<<< orphan*/ ,struct resource*) ; 
 struct resource* get_pci_domain_busn_res (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 scalar_t__ pci_is_root_bus (struct pci_bus*) ; 
 struct resource* request_resource_conflict (struct resource*,struct resource*) ; 

int pci_bus_insert_busn_res(struct pci_bus *b, int bus, int bus_max)
{
	struct resource *res = &b->busn_res;
	struct resource *parent_res, *conflict;

	res->start = bus;
	res->end = bus_max;
	res->flags = IORESOURCE_BUS;

	if (!pci_is_root_bus(b))
		parent_res = &b->parent->busn_res;
	else {
		parent_res = get_pci_domain_busn_res(pci_domain_nr(b));
		res->flags |= IORESOURCE_PCI_FIXED;
	}

	conflict = request_resource_conflict(parent_res, res);

	if (conflict)
		dev_info(&b->dev,
			   "busn_res: can not insert %pR under %s%pR (conflicts with %s %pR)\n",
			    res, pci_is_root_bus(b) ? "domain " : "",
			    parent_res, conflict->name, conflict);

	return conflict == NULL;
}