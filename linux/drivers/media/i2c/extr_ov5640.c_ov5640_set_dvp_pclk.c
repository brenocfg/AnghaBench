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
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5640_REG_SC_PLL_CTRL0 ; 
 int /*<<< orphan*/  OV5640_REG_SC_PLL_CTRL1 ; 
 int /*<<< orphan*/  OV5640_REG_SC_PLL_CTRL2 ; 
 int /*<<< orphan*/  OV5640_REG_SC_PLL_CTRL3 ; 
 int /*<<< orphan*/  OV5640_REG_SYS_ROOT_DIVIDER ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  ov5640_calc_pclk (struct ov5640_dev*,unsigned long,int*,int*,int*,int*,int*,int*) ; 
 int ov5640_mod_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ov5640_set_dvp_pclk(struct ov5640_dev *sensor, unsigned long rate)
{
	u8 prediv, mult, sysdiv, pll_rdiv, bit_div, pclk_div;
	int ret;

	ov5640_calc_pclk(sensor, rate, &prediv, &mult, &sysdiv, &pll_rdiv,
			 &bit_div, &pclk_div);

	if (bit_div == 2)
		bit_div = 8;

	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL0,
			     0x0f, bit_div);
	if (ret)
		return ret;

	/*
	 * We need to set sysdiv according to the clock, and to clear
	 * the MIPI divider.
	 */
	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL1,
			     0xff, sysdiv << 4);
	if (ret)
		return ret;

	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL2,
			     0xff, mult);
	if (ret)
		return ret;

	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL3,
			     0x1f, prediv | ((pll_rdiv - 1) << 4));
	if (ret)
		return ret;

	return ov5640_mod_reg(sensor, OV5640_REG_SYS_ROOT_DIVIDER, 0x30,
			      (ilog2(pclk_div) << 4));
}