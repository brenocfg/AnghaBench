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
struct twl6030_gpadc_data {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int TWL6030_GPADC_MAX_CHANNELS ; 
 int TWL6030_GPADC_NUM_TRIM_REGS ; 
 int /*<<< orphan*/  TWL6030_GPADC_TRIM1 ; 
 int /*<<< orphan*/  TWL6030_MODULE_ID2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  twl6030_calibrate_channel (struct twl6030_gpadc_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6030_gpadc_get_trim_offset (int /*<<< orphan*/ ) ; 
 int twl_i2c_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int twl6030_calibration(struct twl6030_gpadc_data *gpadc)
{
	int ret;
	int chn;
	u8 trim_regs[TWL6030_GPADC_NUM_TRIM_REGS];
	s8 d1, d2;

	/*
	 * for calibration two measurements have been performed at
	 * factory, for some channels, during the production test and
	 * have been stored in registers. This two stored values are
	 * used to correct the measurements. The values represent
	 * offsets for the given input from the output on ideal curve.
	 */
	ret = twl_i2c_read(TWL6030_MODULE_ID2, trim_regs,
			TWL6030_GPADC_TRIM1, TWL6030_GPADC_NUM_TRIM_REGS);
	if (ret < 0) {
		dev_err(gpadc->dev, "calibration failed\n");
		return ret;
	}

	for (chn = 0; chn < TWL6030_GPADC_MAX_CHANNELS; chn++) {

		switch (chn) {
		case 0:
			d1 = trim_regs[0];
			d2 = trim_regs[1];
			break;
		case 1:
		case 3:
		case 4:
		case 5:
		case 6:
			d1 = trim_regs[4];
			d2 = trim_regs[5];
			break;
		case 2:
			d1 = trim_regs[12];
			d2 = trim_regs[13];
			break;
		case 7:
			d1 = trim_regs[6];
			d2 = trim_regs[7];
			break;
		case 8:
			d1 = trim_regs[2];
			d2 = trim_regs[3];
			break;
		case 9:
			d1 = trim_regs[8];
			d2 = trim_regs[9];
			break;
		case 10:
			d1 = trim_regs[10];
			d2 = trim_regs[11];
			break;
		case 14:
			d1 = trim_regs[14];
			d2 = trim_regs[15];
			break;
		default:
			continue;
		}

		d1 = twl6030_gpadc_get_trim_offset(d1);
		d2 = twl6030_gpadc_get_trim_offset(d2);

		twl6030_calibrate_channel(gpadc, chn, d1, d2);
	}

	return 0;
}