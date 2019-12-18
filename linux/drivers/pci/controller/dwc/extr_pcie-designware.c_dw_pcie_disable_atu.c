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
struct dw_pcie {int dummy; } ;
typedef  enum dw_pcie_region_type { ____Placeholder_dw_pcie_region_type } dw_pcie_region_type ;

/* Variables and functions */
#define  DW_PCIE_REGION_INBOUND 129 
#define  DW_PCIE_REGION_OUTBOUND 128 
 int /*<<< orphan*/  PCIE_ATU_CR2 ; 
 scalar_t__ PCIE_ATU_ENABLE ; 
 int PCIE_ATU_REGION_INBOUND ; 
 int PCIE_ATU_REGION_OUTBOUND ; 
 int /*<<< orphan*/  PCIE_ATU_VIEWPORT ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (struct dw_pcie*,int /*<<< orphan*/ ,int) ; 

void dw_pcie_disable_atu(struct dw_pcie *pci, int index,
			 enum dw_pcie_region_type type)
{
	int region;

	switch (type) {
	case DW_PCIE_REGION_INBOUND:
		region = PCIE_ATU_REGION_INBOUND;
		break;
	case DW_PCIE_REGION_OUTBOUND:
		region = PCIE_ATU_REGION_OUTBOUND;
		break;
	default:
		return;
	}

	dw_pcie_writel_dbi(pci, PCIE_ATU_VIEWPORT, region | index);
	dw_pcie_writel_dbi(pci, PCIE_ATU_CR2, (u32)~PCIE_ATU_ENABLE);
}