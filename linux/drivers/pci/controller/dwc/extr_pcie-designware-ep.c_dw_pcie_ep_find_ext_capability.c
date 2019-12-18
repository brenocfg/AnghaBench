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
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int PCI_CFG_SPACE_SIZE ; 
 int PCI_EXT_CAP_ID (int /*<<< orphan*/ ) ; 
 int PCI_EXT_CAP_NEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_readl_dbi (struct dw_pcie*,int) ; 

__attribute__((used)) static unsigned int dw_pcie_ep_find_ext_capability(struct dw_pcie *pci, int cap)
{
	u32 header;
	int pos = PCI_CFG_SPACE_SIZE;

	while (pos) {
		header = dw_pcie_readl_dbi(pci, pos);
		if (PCI_EXT_CAP_ID(header) == cap)
			return pos;

		pos = PCI_EXT_CAP_NEXT(header);
		if (!pos)
			break;
	}

	return 0;
}