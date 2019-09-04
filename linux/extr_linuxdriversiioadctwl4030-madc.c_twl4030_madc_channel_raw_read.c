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
typedef  int u16 ;
struct twl4030_madc_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_MODULE_MADC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int twl_i2c_read_u16 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_madc_channel_raw_read(struct twl4030_madc_data *madc, u8 reg)
{
	u16 val;
	int ret;
	/*
	 * For each ADC channel, we have MSB and LSB register pair. MSB address
	 * is always LSB address+1. reg parameter is the address of LSB register
	 */
	ret = twl_i2c_read_u16(TWL4030_MODULE_MADC, &val, reg);
	if (ret) {
		dev_err(madc->dev, "unable to read register 0x%X\n", reg);
		return ret;
	}

	return (int)(val >> 6);
}