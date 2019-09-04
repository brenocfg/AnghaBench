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
struct twl6030_gpadc_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TWL6030_GPADC_NUM_TRIM_REGS ; 
 int /*<<< orphan*/  TWL6030_GPADC_TRIM1 ; 
 int /*<<< orphan*/  TWL6030_MODULE_ID2 ; 
 int TWL6032_GPADC_MAX_CHANNELS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  twl6030_calibrate_channel (struct twl6030_gpadc_data*,int,int,int) ; 
 int twl6032_get_trim_value (int*,int,int,int,int,int) ; 
 int twl_i2c_read (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int twl6032_calibration(struct twl6030_gpadc_data *gpadc)
{
	int chn, d1 = 0, d2 = 0, temp;
	u8 trim_regs[TWL6030_GPADC_NUM_TRIM_REGS];
	int ret;

	ret = twl_i2c_read(TWL6030_MODULE_ID2, trim_regs,
			TWL6030_GPADC_TRIM1, TWL6030_GPADC_NUM_TRIM_REGS);
	if (ret < 0) {
		dev_err(gpadc->dev, "calibration failed\n");
		return ret;
	}

	/*
	 * Loop to calculate the value needed for returning voltages from
	 * GPADC not values.
	 *
	 * gain is calculated to 3 decimal places fixed point.
	 */
	for (chn = 0; chn < TWL6032_GPADC_MAX_CHANNELS; chn++) {

		switch (chn) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 11:
		case 14:
			d1 = twl6032_get_trim_value(trim_regs, 2, 0, 0x1f,
								0x06, 2);
			d2 = twl6032_get_trim_value(trim_regs, 3, 1, 0x3f,
								0x06, 2);
			break;
		case 8:
			temp = twl6032_get_trim_value(trim_regs, 2, 0, 0x1f,
								0x06, 2);
			d1 = temp + twl6032_get_trim_value(trim_regs, 7, 6,
								0x18, 0x1E, 1);

			temp = twl6032_get_trim_value(trim_regs, 3, 1, 0x3F,
								0x06, 2);
			d2 = temp + twl6032_get_trim_value(trim_regs, 9, 7,
								0x1F, 0x06, 2);
			break;
		case 9:
			temp = twl6032_get_trim_value(trim_regs, 2, 0, 0x1f,
								0x06, 2);
			d1 = temp + twl6032_get_trim_value(trim_regs, 13, 11,
								0x18, 0x1E, 1);

			temp = twl6032_get_trim_value(trim_regs, 3, 1, 0x3f,
								0x06, 2);
			d2 = temp + twl6032_get_trim_value(trim_regs, 15, 13,
								0x1F, 0x06, 1);
			break;
		case 10:
			d1 = twl6032_get_trim_value(trim_regs, 10, 8, 0x0f,
								0x0E, 3);
			d2 = twl6032_get_trim_value(trim_regs, 14, 12, 0x0f,
								0x0E, 3);
			break;
		case 7:
		case 18:
			temp = twl6032_get_trim_value(trim_regs, 2, 0, 0x1f,
								0x06, 2);

			d1 = (trim_regs[4] & 0x7E) >> 1;
			if (trim_regs[4] & 0x01)
				d1 = -d1;
			d1 += temp;

			temp = twl6032_get_trim_value(trim_regs, 3, 1, 0x3f,
								0x06, 2);

			d2 = (trim_regs[5] & 0xFE) >> 1;
			if (trim_regs[5] & 0x01)
				d2 = -d2;

			d2 += temp;
			break;
		default:
			/* No data for other channels */
			continue;
		}

		twl6030_calibrate_channel(gpadc, chn, d1, d2);
	}

	return 0;
}