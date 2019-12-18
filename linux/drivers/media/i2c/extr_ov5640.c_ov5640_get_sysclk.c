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
struct ov5640_dev {int xclk_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OV5640_REG_SC_PLL_CTRL0 ; 
 int /*<<< orphan*/  OV5640_REG_SC_PLL_CTRL1 ; 
 int /*<<< orphan*/  OV5640_REG_SC_PLL_CTRL2 ; 
 int /*<<< orphan*/  OV5640_REG_SC_PLL_CTRL3 ; 
 int /*<<< orphan*/  OV5640_REG_SYS_ROOT_DIVIDER ; 
 int ov5640_read_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ov5640_get_sysclk(struct ov5640_dev *sensor)
{
	 /* calculate sysclk */
	u32 xvclk = sensor->xclk_freq / 10000;
	u32 multiplier, prediv, VCO, sysdiv, pll_rdiv;
	u32 sclk_rdiv_map[] = {1, 2, 4, 8};
	u32 bit_div2x = 1, sclk_rdiv, sysclk;
	u8 temp1, temp2;
	int ret;

	ret = ov5640_read_reg(sensor, OV5640_REG_SC_PLL_CTRL0, &temp1);
	if (ret)
		return ret;
	temp2 = temp1 & 0x0f;
	if (temp2 == 8 || temp2 == 10)
		bit_div2x = temp2 / 2;

	ret = ov5640_read_reg(sensor, OV5640_REG_SC_PLL_CTRL1, &temp1);
	if (ret)
		return ret;
	sysdiv = temp1 >> 4;
	if (sysdiv == 0)
		sysdiv = 16;

	ret = ov5640_read_reg(sensor, OV5640_REG_SC_PLL_CTRL2, &temp1);
	if (ret)
		return ret;
	multiplier = temp1;

	ret = ov5640_read_reg(sensor, OV5640_REG_SC_PLL_CTRL3, &temp1);
	if (ret)
		return ret;
	prediv = temp1 & 0x0f;
	pll_rdiv = ((temp1 >> 4) & 0x01) + 1;

	ret = ov5640_read_reg(sensor, OV5640_REG_SYS_ROOT_DIVIDER, &temp1);
	if (ret)
		return ret;
	temp2 = temp1 & 0x03;
	sclk_rdiv = sclk_rdiv_map[temp2];

	if (!prediv || !sysdiv || !pll_rdiv || !bit_div2x)
		return -EINVAL;

	VCO = xvclk * multiplier / prediv;

	sysclk = VCO / sysdiv / pll_rdiv * 2 / bit_div2x / sclk_rdiv;

	return sysclk;
}