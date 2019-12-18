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
struct cdns_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_CPU_ADDR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_CPU_ADDR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_DESC0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_DESC1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_PCI_ADDR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_pcie_writel (struct cdns_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cdns_pcie_reset_outbound_region(struct cdns_pcie *pcie, u32 r)
{
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR0(r), 0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR1(r), 0);

	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_DESC0(r), 0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_DESC1(r), 0);

	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR0(r), 0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR1(r), 0);
}