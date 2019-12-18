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
struct ls_pcie {int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_PCIE_REGION_OUTBOUND ; 
 int PCIE_IATU_NUM ; 
 int /*<<< orphan*/  dw_pcie_disable_atu (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ls_pcie_disable_outbound_atus(struct ls_pcie *pcie)
{
	int i;

	for (i = 0; i < PCIE_IATU_NUM; i++)
		dw_pcie_disable_atu(pcie->pci, i, DW_PCIE_REGION_OUTBOUND);
}