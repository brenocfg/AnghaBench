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
struct rockchip_lvds {scalar_t__ output; int /*<<< orphan*/  pclk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DISPLAY_OUTPUT_RGB ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RK3288_LVDS_CFG_REG21 ; 
 int RK3288_LVDS_CFG_REG21_TX_ENABLE ; 
 int /*<<< orphan*/  RK3288_LVDS_CFG_REGC ; 
 int RK3288_LVDS_CFG_REGC_PLL_ENABLE ; 
 int /*<<< orphan*/  RK3288_LVDS_CH0_REG0 ; 
 int RK3288_LVDS_CH0_REG0_LANE0_EN ; 
 int RK3288_LVDS_CH0_REG0_LANE1_EN ; 
 int RK3288_LVDS_CH0_REG0_LANE2_EN ; 
 int RK3288_LVDS_CH0_REG0_LANE3_EN ; 
 int RK3288_LVDS_CH0_REG0_LANE4_EN ; 
 int RK3288_LVDS_CH0_REG0_LANECK_EN ; 
 int RK3288_LVDS_CH0_REG0_LVDS_EN ; 
 int RK3288_LVDS_CH0_REG0_TTL_EN ; 
 int /*<<< orphan*/  RK3288_LVDS_CH0_REG1 ; 
 int RK3288_LVDS_CH0_REG1_LANE0_BIAS ; 
 int RK3288_LVDS_CH0_REG1_LANE1_BIAS ; 
 int RK3288_LVDS_CH0_REG1_LANE2_BIAS ; 
 int RK3288_LVDS_CH0_REG1_LANE3_BIAS ; 
 int RK3288_LVDS_CH0_REG1_LANE4_BIAS ; 
 int RK3288_LVDS_CH0_REG1_LANECK_BIAS ; 
 int /*<<< orphan*/  RK3288_LVDS_CH0_REG2 ; 
 int /*<<< orphan*/  RK3288_LVDS_CH0_REG20 ; 
 int RK3288_LVDS_CH0_REG20_LSB ; 
 int RK3288_LVDS_CH0_REG2_LANE0_LVDS_MODE ; 
 int RK3288_LVDS_CH0_REG2_LANE1_LVDS_MODE ; 
 int RK3288_LVDS_CH0_REG2_LANE2_LVDS_MODE ; 
 int RK3288_LVDS_CH0_REG2_LANE3_LVDS_MODE ; 
 int RK3288_LVDS_CH0_REG2_LANE4_LVDS_MODE ; 
 int RK3288_LVDS_CH0_REG2_LANECK_LVDS_MODE ; 
 int RK3288_LVDS_CH0_REG2_RESERVE_ON ; 
 int /*<<< orphan*/  RK3288_LVDS_CH0_REG3 ; 
 int /*<<< orphan*/  RK3288_LVDS_CH0_REG4 ; 
 int RK3288_LVDS_CH0_REG4_LANE0_TTL_MODE ; 
 int RK3288_LVDS_CH0_REG4_LANE1_TTL_MODE ; 
 int RK3288_LVDS_CH0_REG4_LANE2_TTL_MODE ; 
 int RK3288_LVDS_CH0_REG4_LANE3_TTL_MODE ; 
 int RK3288_LVDS_CH0_REG4_LANE4_TTL_MODE ; 
 int RK3288_LVDS_CH0_REG4_LANECK_TTL_MODE ; 
 int /*<<< orphan*/  RK3288_LVDS_CH0_REG5 ; 
 int RK3288_LVDS_CH0_REG5_LANE0_TTL_DATA ; 
 int RK3288_LVDS_CH0_REG5_LANE1_TTL_DATA ; 
 int RK3288_LVDS_CH0_REG5_LANE2_TTL_DATA ; 
 int RK3288_LVDS_CH0_REG5_LANE3_TTL_DATA ; 
 int RK3288_LVDS_CH0_REG5_LANE4_TTL_DATA ; 
 int RK3288_LVDS_CH0_REG5_LANECK_TTL_DATA ; 
 int /*<<< orphan*/  RK3288_LVDS_CH0_REGD ; 
 int RK3288_LVDS_PLL_FBDIV_REG2 (int) ; 
 int RK3288_LVDS_PLL_FBDIV_REG3 (int) ; 
 int RK3288_LVDS_PLL_PREDIV_REGD (int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lvds_writel (struct rockchip_lvds*,int /*<<< orphan*/ ,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_lvds_poweron(struct rockchip_lvds *lvds)
{
	int ret;
	u32 val;

	ret = clk_enable(lvds->pclk);
	if (ret < 0) {
		DRM_DEV_ERROR(lvds->dev, "failed to enable lvds pclk %d\n", ret);
		return ret;
	}
	ret = pm_runtime_get_sync(lvds->dev);
	if (ret < 0) {
		DRM_DEV_ERROR(lvds->dev, "failed to get pm runtime: %d\n", ret);
		clk_disable(lvds->pclk);
		return ret;
	}
	val = RK3288_LVDS_CH0_REG0_LANE4_EN | RK3288_LVDS_CH0_REG0_LANE3_EN |
		RK3288_LVDS_CH0_REG0_LANE2_EN | RK3288_LVDS_CH0_REG0_LANE1_EN |
		RK3288_LVDS_CH0_REG0_LANE0_EN;
	if (lvds->output == DISPLAY_OUTPUT_RGB) {
		val |= RK3288_LVDS_CH0_REG0_TTL_EN |
			RK3288_LVDS_CH0_REG0_LANECK_EN;
		lvds_writel(lvds, RK3288_LVDS_CH0_REG0, val);
		lvds_writel(lvds, RK3288_LVDS_CH0_REG2,
			    RK3288_LVDS_PLL_FBDIV_REG2(0x46));
		lvds_writel(lvds, RK3288_LVDS_CH0_REG4,
			    RK3288_LVDS_CH0_REG4_LANECK_TTL_MODE |
			    RK3288_LVDS_CH0_REG4_LANE4_TTL_MODE |
			    RK3288_LVDS_CH0_REG4_LANE3_TTL_MODE |
			    RK3288_LVDS_CH0_REG4_LANE2_TTL_MODE |
			    RK3288_LVDS_CH0_REG4_LANE1_TTL_MODE |
			    RK3288_LVDS_CH0_REG4_LANE0_TTL_MODE);
		lvds_writel(lvds, RK3288_LVDS_CH0_REG5,
			    RK3288_LVDS_CH0_REG5_LANECK_TTL_DATA |
			    RK3288_LVDS_CH0_REG5_LANE4_TTL_DATA |
			    RK3288_LVDS_CH0_REG5_LANE3_TTL_DATA |
			    RK3288_LVDS_CH0_REG5_LANE2_TTL_DATA |
			    RK3288_LVDS_CH0_REG5_LANE1_TTL_DATA |
			    RK3288_LVDS_CH0_REG5_LANE0_TTL_DATA);
	} else {
		val |= RK3288_LVDS_CH0_REG0_LVDS_EN |
			    RK3288_LVDS_CH0_REG0_LANECK_EN;
		lvds_writel(lvds, RK3288_LVDS_CH0_REG0, val);
		lvds_writel(lvds, RK3288_LVDS_CH0_REG1,
			    RK3288_LVDS_CH0_REG1_LANECK_BIAS |
			    RK3288_LVDS_CH0_REG1_LANE4_BIAS |
			    RK3288_LVDS_CH0_REG1_LANE3_BIAS |
			    RK3288_LVDS_CH0_REG1_LANE2_BIAS |
			    RK3288_LVDS_CH0_REG1_LANE1_BIAS |
			    RK3288_LVDS_CH0_REG1_LANE0_BIAS);
		lvds_writel(lvds, RK3288_LVDS_CH0_REG2,
			    RK3288_LVDS_CH0_REG2_RESERVE_ON |
			    RK3288_LVDS_CH0_REG2_LANECK_LVDS_MODE |
			    RK3288_LVDS_CH0_REG2_LANE4_LVDS_MODE |
			    RK3288_LVDS_CH0_REG2_LANE3_LVDS_MODE |
			    RK3288_LVDS_CH0_REG2_LANE2_LVDS_MODE |
			    RK3288_LVDS_CH0_REG2_LANE1_LVDS_MODE |
			    RK3288_LVDS_CH0_REG2_LANE0_LVDS_MODE |
			    RK3288_LVDS_PLL_FBDIV_REG2(0x46));
		lvds_writel(lvds, RK3288_LVDS_CH0_REG4, 0x00);
		lvds_writel(lvds, RK3288_LVDS_CH0_REG5, 0x00);
	}
	lvds_writel(lvds, RK3288_LVDS_CH0_REG3, RK3288_LVDS_PLL_FBDIV_REG3(0x46));
	lvds_writel(lvds, RK3288_LVDS_CH0_REGD, RK3288_LVDS_PLL_PREDIV_REGD(0x0a));
	lvds_writel(lvds, RK3288_LVDS_CH0_REG20, RK3288_LVDS_CH0_REG20_LSB);

	lvds_writel(lvds, RK3288_LVDS_CFG_REGC, RK3288_LVDS_CFG_REGC_PLL_ENABLE);
	lvds_writel(lvds, RK3288_LVDS_CFG_REG21, RK3288_LVDS_CFG_REG21_TX_ENABLE);

	return 0;
}