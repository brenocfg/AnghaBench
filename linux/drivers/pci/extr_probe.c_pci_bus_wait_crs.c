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
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_FUNC (int) ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ pci_bus_crs_vendor_id (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_bus_read_config_dword (struct pci_bus*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool pci_bus_wait_crs(struct pci_bus *bus, int devfn, u32 *l,
			     int timeout)
{
	int delay = 1;

	if (!pci_bus_crs_vendor_id(*l))
		return true;	/* not a CRS completion */

	if (!timeout)
		return false;	/* CRS, but caller doesn't want to wait */

	/*
	 * We got the reserved Vendor ID that indicates a completion with
	 * Configuration Request Retry Status (CRS).  Retry until we get a
	 * valid Vendor ID or we time out.
	 */
	while (pci_bus_crs_vendor_id(*l)) {
		if (delay > timeout) {
			pr_warn("pci %04x:%02x:%02x.%d: not ready after %dms; giving up\n",
				pci_domain_nr(bus), bus->number,
				PCI_SLOT(devfn), PCI_FUNC(devfn), delay - 1);

			return false;
		}
		if (delay >= 1000)
			pr_info("pci %04x:%02x:%02x.%d: not ready after %dms; waiting\n",
				pci_domain_nr(bus), bus->number,
				PCI_SLOT(devfn), PCI_FUNC(devfn), delay - 1);

		msleep(delay);
		delay *= 2;

		if (pci_bus_read_config_dword(bus, devfn, PCI_VENDOR_ID, l))
			return false;
	}

	if (delay >= 1000)
		pr_info("pci %04x:%02x:%02x.%d: ready after %dms\n",
			pci_domain_nr(bus), bus->number,
			PCI_SLOT(devfn), PCI_FUNC(devfn), delay - 1);

	return true;
}