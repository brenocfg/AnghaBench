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
struct phy {int dummy; } ;
struct exynos_pcie_phy {int /*<<< orphan*/  blk_base; int /*<<< orphan*/  phy_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_PHY_COMMON_RESET ; 
 int /*<<< orphan*/  PCIE_PHY_DCC_FEEDBACK ; 
 int /*<<< orphan*/  PCIE_PHY_IMPEDANCE ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_BIAS ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_DIV_0 ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_DIV_1 ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV0_DRV_LVL ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV0_EMP_LVL ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV0_LVCC ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV0_RXCDR ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV1_EMP_LVL ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV1_LVCC ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV1_RXCDR ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV2_EMP_LVL ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV2_LVCC ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV2_RXCDR ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV3_EMP_LVL ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV3_LVCC ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV3_RXCDR ; 
 int /*<<< orphan*/  exynos_pcie_phy_writel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct exynos_pcie_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int exynos5440_pcie_phy_init(struct phy *phy)
{
	struct exynos_pcie_phy *ep = phy_get_drvdata(phy);

	/* DCC feedback control off */
	exynos_pcie_phy_writel(ep->phy_base, 0x29, PCIE_PHY_DCC_FEEDBACK);

	/* set TX/RX impedance */
	exynos_pcie_phy_writel(ep->phy_base, 0xd5, PCIE_PHY_IMPEDANCE);

	/* set 50Mhz PHY clock */
	exynos_pcie_phy_writel(ep->phy_base, 0x14, PCIE_PHY_PLL_DIV_0);
	exynos_pcie_phy_writel(ep->phy_base, 0x12, PCIE_PHY_PLL_DIV_1);

	/* set TX Differential output for lane 0 */
	exynos_pcie_phy_writel(ep->phy_base, 0x7f, PCIE_PHY_TRSV0_DRV_LVL);

	/* set TX Pre-emphasis Level Control for lane 0 to minimum */
	exynos_pcie_phy_writel(ep->phy_base, 0x0, PCIE_PHY_TRSV0_EMP_LVL);

	/* set RX clock and data recovery bandwidth */
	exynos_pcie_phy_writel(ep->phy_base, 0xe7, PCIE_PHY_PLL_BIAS);
	exynos_pcie_phy_writel(ep->phy_base, 0x82, PCIE_PHY_TRSV0_RXCDR);
	exynos_pcie_phy_writel(ep->phy_base, 0x82, PCIE_PHY_TRSV1_RXCDR);
	exynos_pcie_phy_writel(ep->phy_base, 0x82, PCIE_PHY_TRSV2_RXCDR);
	exynos_pcie_phy_writel(ep->phy_base, 0x82, PCIE_PHY_TRSV3_RXCDR);

	/* change TX Pre-emphasis Level Control for lanes */
	exynos_pcie_phy_writel(ep->phy_base, 0x39, PCIE_PHY_TRSV0_EMP_LVL);
	exynos_pcie_phy_writel(ep->phy_base, 0x39, PCIE_PHY_TRSV1_EMP_LVL);
	exynos_pcie_phy_writel(ep->phy_base, 0x39, PCIE_PHY_TRSV2_EMP_LVL);
	exynos_pcie_phy_writel(ep->phy_base, 0x39, PCIE_PHY_TRSV3_EMP_LVL);

	/* set LVCC */
	exynos_pcie_phy_writel(ep->phy_base, 0x20, PCIE_PHY_TRSV0_LVCC);
	exynos_pcie_phy_writel(ep->phy_base, 0xa0, PCIE_PHY_TRSV1_LVCC);
	exynos_pcie_phy_writel(ep->phy_base, 0xa0, PCIE_PHY_TRSV2_LVCC);
	exynos_pcie_phy_writel(ep->phy_base, 0xa0, PCIE_PHY_TRSV3_LVCC);

	/* pulse for common reset */
	exynos_pcie_phy_writel(ep->blk_base, 1, PCIE_PHY_COMMON_RESET);
	udelay(500);
	exynos_pcie_phy_writel(ep->blk_base, 0, PCIE_PHY_COMMON_RESET);

	return 0;
}