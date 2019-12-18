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
struct gpu_i2c_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ I2C_MST_HYBRID_PADCTL ; 
 int I2C_MST_HYBRID_PADCTL_I2C_SCL_INPUT_RCV ; 
 int I2C_MST_HYBRID_PADCTL_I2C_SDA_INPUT_RCV ; 
 int I2C_MST_HYBRID_PADCTL_MODE_I2C ; 
 scalar_t__ I2C_MST_I2C0_TIMING ; 
 int I2C_MST_I2C0_TIMING_SCL_PERIOD_100KHZ ; 
 int I2C_MST_I2C0_TIMING_TIMEOUT_CHECK ; 
 int I2C_MST_I2C0_TIMING_TIMEOUT_CLK_CNT ; 
 int I2C_MST_I2C0_TIMING_TIMEOUT_CLK_CNT_MAX ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gpu_enable_i2c_bus(struct gpu_i2c_dev *i2cd)
{
	u32 val;

	/* enable I2C */
	val = readl(i2cd->regs + I2C_MST_HYBRID_PADCTL);
	val |= I2C_MST_HYBRID_PADCTL_MODE_I2C |
		I2C_MST_HYBRID_PADCTL_I2C_SCL_INPUT_RCV |
		I2C_MST_HYBRID_PADCTL_I2C_SDA_INPUT_RCV;
	writel(val, i2cd->regs + I2C_MST_HYBRID_PADCTL);

	/* enable 100KHZ mode */
	val = I2C_MST_I2C0_TIMING_SCL_PERIOD_100KHZ;
	val |= (I2C_MST_I2C0_TIMING_TIMEOUT_CLK_CNT_MAX
	    << I2C_MST_I2C0_TIMING_TIMEOUT_CLK_CNT);
	val |= I2C_MST_I2C0_TIMING_TIMEOUT_CHECK;
	writel(val, i2cd->regs + I2C_MST_I2C0_TIMING);
}