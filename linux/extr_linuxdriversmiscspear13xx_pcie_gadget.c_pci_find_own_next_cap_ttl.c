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
 int PCI_CAP_LIST_ID ; 
 scalar_t__ PCI_CAP_LIST_NEXT ; 
 int /*<<< orphan*/  spear_dbi_read_reg (struct spear_pcie_gadget_config*,int,int,int*) ; 

__attribute__((used)) static int pci_find_own_next_cap_ttl(struct spear_pcie_gadget_config *config,
		u32 pos, int cap, int *ttl)
{
	u32 id;

	while ((*ttl)--) {
		spear_dbi_read_reg(config, pos, 1, &pos);
		if (pos < 0x40)
			break;
		pos &= ~3;
		spear_dbi_read_reg(config, pos + PCI_CAP_LIST_ID, 1, &id);
		if (id == 0xff)
			break;
		if (id == cap)
			return pos;
		pos += PCI_CAP_LIST_NEXT;
	}
	return 0;
}