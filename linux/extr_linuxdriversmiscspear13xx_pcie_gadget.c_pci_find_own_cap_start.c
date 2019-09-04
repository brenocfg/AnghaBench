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
typedef  int u8 ;
typedef  int u32 ;
struct spear_pcie_gadget_config {int dummy; } ;

/* Variables and functions */
 int PCI_CAPABILITY_LIST ; 
 int PCI_CB_CAPABILITY_LIST ; 
#define  PCI_HEADER_TYPE_BRIDGE 130 
#define  PCI_HEADER_TYPE_CARDBUS 129 
#define  PCI_HEADER_TYPE_NORMAL 128 
 int /*<<< orphan*/  PCI_STATUS ; 
 int PCI_STATUS_CAP_LIST ; 
 int /*<<< orphan*/  spear_dbi_read_reg (struct spear_pcie_gadget_config*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int pci_find_own_cap_start(struct spear_pcie_gadget_config *config,
				u8 hdr_type)
{
	u32 status;

	spear_dbi_read_reg(config, PCI_STATUS, 2, &status);
	if (!(status & PCI_STATUS_CAP_LIST))
		return 0;

	switch (hdr_type) {
	case PCI_HEADER_TYPE_NORMAL:
	case PCI_HEADER_TYPE_BRIDGE:
		return PCI_CAPABILITY_LIST;
	case PCI_HEADER_TYPE_CARDBUS:
		return PCI_CB_CAPABILITY_LIST;
	default:
		return 0;
	}

	return 0;
}