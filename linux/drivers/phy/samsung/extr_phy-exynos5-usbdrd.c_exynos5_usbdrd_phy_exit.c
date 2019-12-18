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
struct phy_usb_instance {int dummy; } ;
struct phy {int dummy; } ;
struct exynos5_usbdrd_phy {int /*<<< orphan*/  clk; scalar_t__ reg_phy; } ;

/* Variables and functions */
 scalar_t__ EXYNOS5_DRD_PHYCLKRST ; 
 scalar_t__ EXYNOS5_DRD_PHYTEST ; 
 scalar_t__ EXYNOS5_DRD_PHYUTMI ; 
 int PHYCLKRST_COMMONONN ; 
 int PHYCLKRST_REF_SSP_EN ; 
 int PHYCLKRST_SSC_EN ; 
 int PHYTEST_POWERDOWN_HSP ; 
 int PHYTEST_POWERDOWN_SSP ; 
 int PHYUTMI_FORCESLEEP ; 
 int PHYUTMI_FORCESUSPEND ; 
 int PHYUTMI_OTGDISABLE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct phy_usb_instance* phy_get_drvdata (struct phy*) ; 
 int readl (scalar_t__) ; 
 struct exynos5_usbdrd_phy* to_usbdrd_phy (struct phy_usb_instance*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int exynos5_usbdrd_phy_exit(struct phy *phy)
{
	int ret;
	u32 reg;
	struct phy_usb_instance *inst = phy_get_drvdata(phy);
	struct exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	ret = clk_prepare_enable(phy_drd->clk);
	if (ret)
		return ret;

	reg =	PHYUTMI_OTGDISABLE |
		PHYUTMI_FORCESUSPEND |
		PHYUTMI_FORCESLEEP;
	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYUTMI);

	/* Resetting the PHYCLKRST enable bits to reduce leakage current */
	reg = readl(phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);
	reg &= ~(PHYCLKRST_REF_SSP_EN |
		 PHYCLKRST_SSC_EN |
		 PHYCLKRST_COMMONONN);
	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);

	/* Control PHYTEST to remove leakage current */
	reg = readl(phy_drd->reg_phy + EXYNOS5_DRD_PHYTEST);
	reg |=	PHYTEST_POWERDOWN_SSP |
		PHYTEST_POWERDOWN_HSP;
	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYTEST);

	clk_disable_unprepare(phy_drd->clk);

	return 0;
}