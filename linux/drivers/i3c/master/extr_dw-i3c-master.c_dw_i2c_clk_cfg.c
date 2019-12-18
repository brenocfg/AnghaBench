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
typedef  unsigned long u16 ;
struct dw_i3c_master {scalar_t__ regs; int /*<<< orphan*/  core_clk; } ;

/* Variables and functions */
 scalar_t__ BUS_FREE_TIMING ; 
 int BUS_I3C_MST_FREE (unsigned long) ; 
 scalar_t__ DEVICE_CTRL ; 
 int DEV_CTRL_I2C_SLAVE_PRESENT ; 
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int EINVAL ; 
 unsigned long I3C_BUS_I2C_FMP_TLOW_MIN_NS ; 
 unsigned long I3C_BUS_I2C_FM_PLUS_SCL_RATE ; 
 unsigned long I3C_BUS_I2C_FM_SCL_RATE ; 
 unsigned long I3C_BUS_I2C_FM_TLOW_MIN_NS ; 
 scalar_t__ SCL_I2C_FMP_TIMING ; 
 int SCL_I2C_FMP_TIMING_HCNT (unsigned long) ; 
 int SCL_I2C_FMP_TIMING_LCNT (unsigned long) ; 
 scalar_t__ SCL_I2C_FM_TIMING ; 
 int SCL_I2C_FM_TIMING_HCNT (unsigned long) ; 
 int SCL_I2C_FM_TIMING_LCNT (unsigned long) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int dw_i2c_clk_cfg(struct dw_i3c_master *master)
{
	unsigned long core_rate, core_period;
	u16 hcnt, lcnt;
	u32 scl_timing;

	core_rate = clk_get_rate(master->core_clk);
	if (!core_rate)
		return -EINVAL;

	core_period = DIV_ROUND_UP(1000000000, core_rate);

	lcnt = DIV_ROUND_UP(I3C_BUS_I2C_FMP_TLOW_MIN_NS, core_period);
	hcnt = DIV_ROUND_UP(core_rate, I3C_BUS_I2C_FM_PLUS_SCL_RATE) - lcnt;
	scl_timing = SCL_I2C_FMP_TIMING_HCNT(hcnt) |
		     SCL_I2C_FMP_TIMING_LCNT(lcnt);
	writel(scl_timing, master->regs + SCL_I2C_FMP_TIMING);

	lcnt = DIV_ROUND_UP(I3C_BUS_I2C_FM_TLOW_MIN_NS, core_period);
	hcnt = DIV_ROUND_UP(core_rate, I3C_BUS_I2C_FM_SCL_RATE) - lcnt;
	scl_timing = SCL_I2C_FM_TIMING_HCNT(hcnt) |
		     SCL_I2C_FM_TIMING_LCNT(lcnt);
	writel(scl_timing, master->regs + SCL_I2C_FM_TIMING);

	writel(BUS_I3C_MST_FREE(lcnt), master->regs + BUS_FREE_TIMING);
	writel(readl(master->regs + DEVICE_CTRL) | DEV_CTRL_I2C_SLAVE_PRESENT,
	       master->regs + DEVICE_CTRL);

	return 0;
}