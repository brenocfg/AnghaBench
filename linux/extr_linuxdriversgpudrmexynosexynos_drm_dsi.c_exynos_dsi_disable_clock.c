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
struct exynos_dsi {int dummy; } ;

/* Variables and functions */
 int DSIM_BYTE_CLKEN ; 
 int /*<<< orphan*/  DSIM_CLKCTRL_REG ; 
 int DSIM_ESC_CLKEN ; 
 int DSIM_LANE_ESC_CLK_EN_CLK ; 
 int DSIM_LANE_ESC_CLK_EN_DATA_MASK ; 
 int /*<<< orphan*/  DSIM_PLLCTRL_REG ; 
 int DSIM_PLL_EN ; 
 int exynos_dsi_read (struct exynos_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_dsi_write (struct exynos_dsi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void exynos_dsi_disable_clock(struct exynos_dsi *dsi)
{
	u32 reg;

	reg = exynos_dsi_read(dsi, DSIM_CLKCTRL_REG);
	reg &= ~(DSIM_LANE_ESC_CLK_EN_CLK | DSIM_LANE_ESC_CLK_EN_DATA_MASK
			| DSIM_ESC_CLKEN | DSIM_BYTE_CLKEN);
	exynos_dsi_write(dsi, DSIM_CLKCTRL_REG, reg);

	reg = exynos_dsi_read(dsi, DSIM_PLLCTRL_REG);
	reg &= ~DSIM_PLL_EN;
	exynos_dsi_write(dsi, DSIM_PLLCTRL_REG, reg);
}