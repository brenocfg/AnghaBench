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
struct stm_thermal_sensor {scalar_t__ base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int CALIBRATION_CONTROL ; 
 scalar_t__ DTS_CFGR1_OFFSET ; 
 int EINVAL ; 
 int HSREF_CLK_DIV_MASK ; 
 int HSREF_CLK_DIV_POS ; 
 int NO_HW_TRIG ; 
 int ONE_MHZ ; 
 int REFCLK_SEL ; 
 int TS1_INTRIG_SEL_MASK ; 
 int TS1_SMP_TIME_MASK ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm_thermal_calibration(struct stm_thermal_sensor *sensor)
{
	u32 value, clk_freq;
	u32 prescaler;

	/* Figure out prescaler value for PCLK during calibration */
	clk_freq = clk_get_rate(sensor->clk);
	if (!clk_freq)
		return -EINVAL;

	prescaler = 0;
	clk_freq /= ONE_MHZ;
	if (clk_freq) {
		while (prescaler <= clk_freq)
			prescaler++;
	}

	value = readl_relaxed(sensor->base + DTS_CFGR1_OFFSET);

	/* Clear prescaler */
	value &= ~HSREF_CLK_DIV_MASK;

	/* Set prescaler. pclk_freq/prescaler < 1MHz */
	value |= (prescaler << HSREF_CLK_DIV_POS);

	/* Select PCLK as reference clock */
	value &= ~REFCLK_SEL;

	/* Set maximal sampling time for better precision */
	value |= TS1_SMP_TIME_MASK;

	/* Measure with calibration */
	value &= ~CALIBRATION_CONTROL;

	/* select trigger */
	value &= ~TS1_INTRIG_SEL_MASK;
	value |= NO_HW_TRIG;

	writel_relaxed(value, sensor->base + DTS_CFGR1_OFFSET);

	return 0;
}