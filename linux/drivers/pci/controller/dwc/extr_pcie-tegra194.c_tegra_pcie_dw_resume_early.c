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
struct tegra_pcie_dw {int /*<<< orphan*/  link_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_CTRL ; 
 int APPL_CTRL_HW_HOT_RST_EN ; 
 int APPL_CTRL_HW_HOT_RST_MODE_IMDT_RST ; 
 int APPL_CTRL_HW_HOT_RST_MODE_MASK ; 
 int APPL_CTRL_HW_HOT_RST_MODE_SHIFT ; 
 int appl_readl (struct tegra_pcie_dw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appl_writel (struct tegra_pcie_dw*,int,int /*<<< orphan*/ ) ; 
 struct tegra_pcie_dw* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int tegra_pcie_dw_resume_early(struct device *dev)
{
	struct tegra_pcie_dw *pcie = dev_get_drvdata(dev);
	u32 val;

	if (!pcie->link_state)
		return 0;

	/* Disable HW_HOT_RST mode */
	val = appl_readl(pcie, APPL_CTRL);
	val &= ~(APPL_CTRL_HW_HOT_RST_MODE_MASK <<
		 APPL_CTRL_HW_HOT_RST_MODE_SHIFT);
	val |= APPL_CTRL_HW_HOT_RST_MODE_IMDT_RST <<
	       APPL_CTRL_HW_HOT_RST_MODE_SHIFT;
	val &= ~APPL_CTRL_HW_HOT_RST_EN;
	appl_writel(pcie, val, APPL_CTRL);

	return 0;
}