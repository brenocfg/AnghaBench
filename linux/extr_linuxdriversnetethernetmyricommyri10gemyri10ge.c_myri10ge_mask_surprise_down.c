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
typedef  int u32 ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 scalar_t__ PCI_ERR_UNCOR_MASK ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 

__attribute__((used)) static void myri10ge_mask_surprise_down(struct pci_dev *pdev)
{
	struct pci_dev *bridge = pdev->bus->self;
	int cap;
	u32 mask;

	if (bridge == NULL)
		return;

	cap = pci_find_ext_capability(bridge, PCI_EXT_CAP_ID_ERR);
	if (cap) {
		/* a sram parity error can cause a surprise link
		 * down; since we expect and can recover from sram
		 * parity errors, mask surprise link down events */
		pci_read_config_dword(bridge, cap + PCI_ERR_UNCOR_MASK, &mask);
		mask |= 0x20;
		pci_write_config_dword(bridge, cap + PCI_ERR_UNCOR_MASK, mask);
	}
}