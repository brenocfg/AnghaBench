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
struct tegra_pcie_dw {scalar_t__ appl_base; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 scalar_t__ APPL_DEBUG ; 
 int APPL_DEBUG_PM_LINKST_IN_L2_LAT ; 
 int APPL_PM_XMT_TURNOFF_STATE ; 
 int /*<<< orphan*/  APPL_RADM_STATUS ; 
 int /*<<< orphan*/  PME_ACK_TIMEOUT ; 
 int appl_readl (struct tegra_pcie_dw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appl_writel (struct tegra_pcie_dw*,int,int /*<<< orphan*/ ) ; 
 int readl_poll_timeout_atomic (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_pcie_dw_link_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_pcie_try_link_l2(struct tegra_pcie_dw *pcie)
{
	u32 val;

	if (!tegra_pcie_dw_link_up(&pcie->pci))
		return 0;

	val = appl_readl(pcie, APPL_RADM_STATUS);
	val |= APPL_PM_XMT_TURNOFF_STATE;
	appl_writel(pcie, val, APPL_RADM_STATUS);

	return readl_poll_timeout_atomic(pcie->appl_base + APPL_DEBUG, val,
				 val & APPL_DEBUG_PM_LINKST_IN_L2_LAT,
				 1, PME_ACK_TIMEOUT);
}