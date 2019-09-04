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
typedef  int /*<<< orphan*/  u8 ;
struct twl4030_madc_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_MADC_CTRL1 ; 
 int /*<<< orphan*/  TWL4030_MADC_MADCON ; 
 int /*<<< orphan*/  TWL4030_MODULE_MADC ; 
 int /*<<< orphan*/  TWL_MODULE_MAIN_CHARGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_madc_set_power(struct twl4030_madc_data *madc, int on)
{
	u8 regval;
	int ret;

	ret = twl_i2c_read_u8(TWL_MODULE_MAIN_CHARGE,
			      &regval, TWL4030_MADC_CTRL1);
	if (ret) {
		dev_err(madc->dev, "unable to read madc ctrl1 reg 0x%X\n",
			TWL4030_MADC_CTRL1);
		return ret;
	}
	if (on)
		regval |= TWL4030_MADC_MADCON;
	else
		regval &= ~TWL4030_MADC_MADCON;
	ret = twl_i2c_write_u8(TWL4030_MODULE_MADC, regval, TWL4030_MADC_CTRL1);
	if (ret) {
		dev_err(madc->dev, "unable to write madc ctrl1 reg 0x%X\n",
			TWL4030_MADC_CTRL1);
		return ret;
	}

	return 0;
}