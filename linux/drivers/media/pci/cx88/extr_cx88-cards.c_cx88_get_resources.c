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
struct pci_dev {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  devfn; } ;
struct cx88_core {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_mem_region (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cx88_get_resources(const struct cx88_core *core, struct pci_dev *pci)
{
	if (request_mem_region(pci_resource_start(pci, 0),
			       pci_resource_len(pci, 0),
			       core->name))
		return 0;
	pr_err("func %d: Can't get MMIO memory @ 0x%llx, subsystem: %04x:%04x\n",
	       PCI_FUNC(pci->devfn),
	       (unsigned long long)pci_resource_start(pci, 0),
	       pci->subsystem_vendor, pci->subsystem_device);
	return -EBUSY;
}