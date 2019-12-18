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
typedef  int u8 ;
typedef  int u32 ;
struct dw_i3c_master {scalar_t__ regs; int /*<<< orphan*/  core_clk; } ;

/* Variables and functions */
 scalar_t__ BUS_FREE_TIMING ; 
 int BUS_I3C_MST_FREE (int) ; 
 scalar_t__ DEVICE_CTRL ; 
 int DEV_CTRL_I2C_SLAVE_PRESENT ; 
 int DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int EINVAL ; 
 unsigned long I3C_BUS_SDR1_SCL_RATE ; 
 unsigned long I3C_BUS_SDR2_SCL_RATE ; 
 unsigned long I3C_BUS_SDR3_SCL_RATE ; 
 unsigned long I3C_BUS_SDR4_SCL_RATE ; 
 unsigned long I3C_BUS_THIGH_MAX_NS ; 
 unsigned long I3C_BUS_TLOW_OD_MIN_NS ; 
 unsigned long I3C_BUS_TYP_I3C_SCL_RATE ; 
 int SCL_EXT_LCNT_1 (int) ; 
 int SCL_EXT_LCNT_2 (int) ; 
 int SCL_EXT_LCNT_3 (int) ; 
 int SCL_EXT_LCNT_4 (int) ; 
 scalar_t__ SCL_EXT_LCNT_TIMING ; 
 scalar_t__ SCL_I3C_OD_TIMING ; 
 scalar_t__ SCL_I3C_PP_TIMING ; 
 int SCL_I3C_TIMING_CNT_MIN ; 
 int SCL_I3C_TIMING_HCNT (int) ; 
 int SCL_I3C_TIMING_LCNT (int) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int dw_i3c_clk_cfg(struct dw_i3c_master *master)
{
	unsigned long core_rate, core_period;
	u32 scl_timing;
	u8 hcnt, lcnt;

	core_rate = clk_get_rate(master->core_clk);
	if (!core_rate)
		return -EINVAL;

	core_period = DIV_ROUND_UP(1000000000, core_rate);

	hcnt = DIV_ROUND_UP(I3C_BUS_THIGH_MAX_NS, core_period) - 1;
	if (hcnt < SCL_I3C_TIMING_CNT_MIN)
		hcnt = SCL_I3C_TIMING_CNT_MIN;

	lcnt = DIV_ROUND_UP(core_rate, I3C_BUS_TYP_I3C_SCL_RATE) - hcnt;
	if (lcnt < SCL_I3C_TIMING_CNT_MIN)
		lcnt = SCL_I3C_TIMING_CNT_MIN;

	scl_timing = SCL_I3C_TIMING_HCNT(hcnt) | SCL_I3C_TIMING_LCNT(lcnt);
	writel(scl_timing, master->regs + SCL_I3C_PP_TIMING);

	if (!(readl(master->regs + DEVICE_CTRL) & DEV_CTRL_I2C_SLAVE_PRESENT))
		writel(BUS_I3C_MST_FREE(lcnt), master->regs + BUS_FREE_TIMING);

	lcnt = DIV_ROUND_UP(I3C_BUS_TLOW_OD_MIN_NS, core_period);
	scl_timing = SCL_I3C_TIMING_HCNT(hcnt) | SCL_I3C_TIMING_LCNT(lcnt);
	writel(scl_timing, master->regs + SCL_I3C_OD_TIMING);

	lcnt = DIV_ROUND_UP(core_rate, I3C_BUS_SDR1_SCL_RATE) - hcnt;
	scl_timing = SCL_EXT_LCNT_1(lcnt);
	lcnt = DIV_ROUND_UP(core_rate, I3C_BUS_SDR2_SCL_RATE) - hcnt;
	scl_timing |= SCL_EXT_LCNT_2(lcnt);
	lcnt = DIV_ROUND_UP(core_rate, I3C_BUS_SDR3_SCL_RATE) - hcnt;
	scl_timing |= SCL_EXT_LCNT_3(lcnt);
	lcnt = DIV_ROUND_UP(core_rate, I3C_BUS_SDR4_SCL_RATE) - hcnt;
	scl_timing |= SCL_EXT_LCNT_4(lcnt);
	writel(scl_timing, master->regs + SCL_EXT_LCNT_TIMING);

	return 0;
}