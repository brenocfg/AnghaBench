#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rockchip_lvds {int /*<<< orphan*/  pclk; int /*<<< orphan*/  dev; TYPE_1__* soc_data; int /*<<< orphan*/  grf; } ;
struct TYPE_2__ {int /*<<< orphan*/  grf_soc_con7; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int LVDS_CH0_EN ; 
 int LVDS_CH1_EN ; 
 int LVDS_DUAL ; 
 int LVDS_PWRDN ; 
 int LVDS_TTL_EN ; 
 int /*<<< orphan*/  RK3288_LVDS_CFG_REG21 ; 
 int /*<<< orphan*/  RK3288_LVDS_CFG_REG21_TX_ENABLE ; 
 int /*<<< orphan*/  RK3288_LVDS_CFG_REGC ; 
 int /*<<< orphan*/  RK3288_LVDS_CFG_REGC_PLL_ENABLE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lvds_writel (struct rockchip_lvds*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rockchip_lvds_poweroff(struct rockchip_lvds *lvds)
{
	int ret;
	u32 val;

	lvds_writel(lvds, RK3288_LVDS_CFG_REG21, RK3288_LVDS_CFG_REG21_TX_ENABLE);
	lvds_writel(lvds, RK3288_LVDS_CFG_REGC, RK3288_LVDS_CFG_REGC_PLL_ENABLE);
	val = LVDS_DUAL | LVDS_TTL_EN | LVDS_CH0_EN | LVDS_CH1_EN | LVDS_PWRDN;
	val |= val << 16;
	ret = regmap_write(lvds->grf, lvds->soc_data->grf_soc_con7, val);
	if (ret != 0)
		DRM_DEV_ERROR(lvds->dev, "Could not write to GRF: %d\n", ret);

	pm_runtime_put(lvds->dev);
	clk_disable(lvds->pclk);
}