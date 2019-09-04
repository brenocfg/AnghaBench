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
struct exynos_dsi {int /*<<< orphan*/  lanes; int /*<<< orphan*/  dev; int /*<<< orphan*/  esc_clk_rate; int /*<<< orphan*/  burst_clk_rate; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 unsigned long DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int DSIM_BYTE_CLKEN ; 
 int DSIM_BYTE_CLK_SRC (int /*<<< orphan*/ ) ; 
 int DSIM_BYTE_CLK_SRC_MASK ; 
 int /*<<< orphan*/  DSIM_CLKCTRL_REG ; 
 int DSIM_ESC_CLKEN ; 
 int DSIM_ESC_PRESCALER (unsigned long) ; 
 int DSIM_ESC_PRESCALER_MASK ; 
 int DSIM_LANE_ESC_CLK_EN_CLK ; 
 int DSIM_LANE_ESC_CLK_EN_DATA (scalar_t__) ; 
 int DSIM_LANE_ESC_CLK_EN_DATA_MASK ; 
 int DSIM_PLL_BYPASS ; 
 int DSIM_TX_REQUEST_HSCLK ; 
 int EFAULT ; 
 int MHZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int exynos_dsi_read (struct exynos_dsi*,int /*<<< orphan*/ ) ; 
 unsigned long exynos_dsi_set_pll (struct exynos_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_dsi_write (struct exynos_dsi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int exynos_dsi_enable_clock(struct exynos_dsi *dsi)
{
	unsigned long hs_clk, byte_clk, esc_clk;
	unsigned long esc_div;
	u32 reg;

	hs_clk = exynos_dsi_set_pll(dsi, dsi->burst_clk_rate);
	if (!hs_clk) {
		dev_err(dsi->dev, "failed to configure DSI PLL\n");
		return -EFAULT;
	}

	byte_clk = hs_clk / 8;
	esc_div = DIV_ROUND_UP(byte_clk, dsi->esc_clk_rate);
	esc_clk = byte_clk / esc_div;

	if (esc_clk > 20 * MHZ) {
		++esc_div;
		esc_clk = byte_clk / esc_div;
	}

	dev_dbg(dsi->dev, "hs_clk = %lu, byte_clk = %lu, esc_clk = %lu\n",
		hs_clk, byte_clk, esc_clk);

	reg = exynos_dsi_read(dsi, DSIM_CLKCTRL_REG);
	reg &= ~(DSIM_ESC_PRESCALER_MASK | DSIM_LANE_ESC_CLK_EN_CLK
			| DSIM_LANE_ESC_CLK_EN_DATA_MASK | DSIM_PLL_BYPASS
			| DSIM_BYTE_CLK_SRC_MASK);
	reg |= DSIM_ESC_CLKEN | DSIM_BYTE_CLKEN
			| DSIM_ESC_PRESCALER(esc_div)
			| DSIM_LANE_ESC_CLK_EN_CLK
			| DSIM_LANE_ESC_CLK_EN_DATA(BIT(dsi->lanes) - 1)
			| DSIM_BYTE_CLK_SRC(0)
			| DSIM_TX_REQUEST_HSCLK;
	exynos_dsi_write(dsi, DSIM_CLKCTRL_REG, reg);

	return 0;
}