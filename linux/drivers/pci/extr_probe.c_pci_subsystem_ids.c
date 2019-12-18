#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {TYPE_2__* physfn; scalar_t__ is_virtfn; } ;
struct TYPE_4__ {TYPE_1__* sriov; } ;
struct TYPE_3__ {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_SUBSYSTEM_ID ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_VENDOR_ID ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_subsystem_ids(struct pci_dev *dev, u16 *vendor, u16 *device)
{
#ifdef CONFIG_PCI_IOV
	if (dev->is_virtfn) {
		*vendor = dev->physfn->sriov->subsystem_vendor;
		*device = dev->physfn->sriov->subsystem_device;
		return;
	}
#endif
	pci_read_config_word(dev, PCI_SUBSYSTEM_VENDOR_ID, vendor);
	pci_read_config_word(dev, PCI_SUBSYSTEM_ID, device);
}