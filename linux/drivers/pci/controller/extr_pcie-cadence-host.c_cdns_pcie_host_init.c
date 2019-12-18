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
struct resource {int /*<<< orphan*/  start; } ;
struct list_head {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;
struct cdns_pcie_rc {TYPE_1__ pcie; struct resource* bus_range; } ;

/* Variables and functions */
 int cdns_pcie_host_init_address_translation (struct cdns_pcie_rc*) ; 
 int cdns_pcie_host_init_root_port (struct cdns_pcie_rc*) ; 
 int /*<<< orphan*/  pci_free_resource_list (struct list_head*) ; 
 int pci_parse_request_of_pci_ranges (struct device*,struct list_head*,struct resource**) ; 

__attribute__((used)) static int cdns_pcie_host_init(struct device *dev,
			       struct list_head *resources,
			       struct cdns_pcie_rc *rc)
{
	struct resource *bus_range = NULL;
	int err;

	/* Parse our PCI ranges and request their resources */
	err = pci_parse_request_of_pci_ranges(dev, resources, &bus_range);
	if (err)
		return err;

	rc->bus_range = bus_range;
	rc->pcie.bus = bus_range->start;

	err = cdns_pcie_host_init_root_port(rc);
	if (err)
		goto err_out;

	err = cdns_pcie_host_init_address_translation(rc);
	if (err)
		goto err_out;

	return 0;

 err_out:
	pci_free_resource_list(resources);
	return err;
}