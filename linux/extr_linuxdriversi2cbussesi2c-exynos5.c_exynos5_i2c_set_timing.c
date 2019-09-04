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
struct exynos5_i2c {unsigned int op_clock; scalar_t__ regs; int /*<<< orphan*/  dev; TYPE_1__* variant; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {scalar_t__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HSI2C_CONF ; 
 unsigned int HSI2C_FS_TX_CLOCK ; 
 unsigned int HSI2C_HS_TX_CLOCK ; 
 scalar_t__ HSI2C_TIMING_FS1 ; 
 scalar_t__ HSI2C_TIMING_FS2 ; 
 scalar_t__ HSI2C_TIMING_FS3 ; 
 scalar_t__ HSI2C_TIMING_HS1 ; 
 scalar_t__ HSI2C_TIMING_HS2 ; 
 scalar_t__ HSI2C_TIMING_HS3 ; 
 scalar_t__ HSI2C_TIMING_SLA ; 
 scalar_t__ I2C_TYPE_EXYNOS7 ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int exynos5_i2c_set_timing(struct exynos5_i2c *i2c, bool hs_timings)
{
	u32 i2c_timing_s1;
	u32 i2c_timing_s2;
	u32 i2c_timing_s3;
	u32 i2c_timing_sla;
	unsigned int t_start_su, t_start_hd;
	unsigned int t_stop_su;
	unsigned int t_data_su, t_data_hd;
	unsigned int t_scl_l, t_scl_h;
	unsigned int t_sr_release;
	unsigned int t_ftl_cycle;
	unsigned int clkin = clk_get_rate(i2c->clk);
	unsigned int op_clk = hs_timings ? i2c->op_clock :
		(i2c->op_clock >= HSI2C_HS_TX_CLOCK) ? HSI2C_FS_TX_CLOCK :
		i2c->op_clock;
	int div, clk_cycle, temp;

	/*
	 * In case of HSI2C controller in Exynos5 series
	 * FPCLK / FI2C =
	 * (CLK_DIV + 1) * (TSCLK_L + TSCLK_H + 2) + 8 + 2 * FLT_CYCLE
	 *
	 * In case of HSI2C controllers in Exynos7 series
	 * FPCLK / FI2C =
	 * (CLK_DIV + 1) * (TSCLK_L + TSCLK_H + 2) + 8 + FLT_CYCLE
	 *
	 * clk_cycle := TSCLK_L + TSCLK_H
	 * temp := (CLK_DIV + 1) * (clk_cycle + 2)
	 *
	 * Constraints: 4 <= temp, 0 <= CLK_DIV < 256, 2 <= clk_cycle <= 510
	 *
	 */
	t_ftl_cycle = (readl(i2c->regs + HSI2C_CONF) >> 16) & 0x7;
	temp = clkin / op_clk - 8 - t_ftl_cycle;
	if (i2c->variant->hw != I2C_TYPE_EXYNOS7)
		temp -= t_ftl_cycle;
	div = temp / 512;
	clk_cycle = temp / (div + 1) - 2;
	if (temp < 4 || div >= 256 || clk_cycle < 2) {
		dev_err(i2c->dev, "%s clock set-up failed\n",
			hs_timings ? "HS" : "FS");
		return -EINVAL;
	}

	t_scl_l = clk_cycle / 2;
	t_scl_h = clk_cycle / 2;
	t_start_su = t_scl_l;
	t_start_hd = t_scl_l;
	t_stop_su = t_scl_l;
	t_data_su = t_scl_l / 2;
	t_data_hd = t_scl_l / 2;
	t_sr_release = clk_cycle;

	i2c_timing_s1 = t_start_su << 24 | t_start_hd << 16 | t_stop_su << 8;
	i2c_timing_s2 = t_data_su << 24 | t_scl_l << 8 | t_scl_h << 0;
	i2c_timing_s3 = div << 16 | t_sr_release << 0;
	i2c_timing_sla = t_data_hd << 0;

	dev_dbg(i2c->dev, "tSTART_SU: %X, tSTART_HD: %X, tSTOP_SU: %X\n",
		t_start_su, t_start_hd, t_stop_su);
	dev_dbg(i2c->dev, "tDATA_SU: %X, tSCL_L: %X, tSCL_H: %X\n",
		t_data_su, t_scl_l, t_scl_h);
	dev_dbg(i2c->dev, "nClkDiv: %X, tSR_RELEASE: %X\n",
		div, t_sr_release);
	dev_dbg(i2c->dev, "tDATA_HD: %X\n", t_data_hd);

	if (hs_timings) {
		writel(i2c_timing_s1, i2c->regs + HSI2C_TIMING_HS1);
		writel(i2c_timing_s2, i2c->regs + HSI2C_TIMING_HS2);
		writel(i2c_timing_s3, i2c->regs + HSI2C_TIMING_HS3);
	} else {
		writel(i2c_timing_s1, i2c->regs + HSI2C_TIMING_FS1);
		writel(i2c_timing_s2, i2c->regs + HSI2C_TIMING_FS2);
		writel(i2c_timing_s3, i2c->regs + HSI2C_TIMING_FS3);
	}
	writel(i2c_timing_sla, i2c->regs + HSI2C_TIMING_SLA);

	return 0;
}