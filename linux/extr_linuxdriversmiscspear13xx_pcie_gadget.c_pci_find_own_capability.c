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
typedef  int u32 ;
struct spear_pcie_gadget_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_HEADER_TYPE ; 
 int pci_find_own_cap_start (struct spear_pcie_gadget_config*,int) ; 
 int pci_find_own_next_cap (struct spear_pcie_gadget_config*,int,int) ; 
 int /*<<< orphan*/  spear_dbi_read_reg (struct spear_pcie_gadget_config*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int pci_find_own_capability(struct spear_pcie_gadget_config *config,
		int cap)
{
	u32 pos;
	u32 hdr_type;

	spear_dbi_read_reg(config, PCI_HEADER_TYPE, 1, &hdr_type);

	pos = pci_find_own_cap_start(config, hdr_type);
	if (pos)
		pos = pci_find_own_next_cap(config, pos, cap);

	return pos;
}