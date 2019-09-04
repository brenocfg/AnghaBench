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

/* Variables and functions */
 int /*<<< orphan*/  REG_BCICTL2 ; 
 int TEMP_PSR_R ; 
 int TEMP_STEP_SIZE ; 
 int TWL4030_BCI_ITHSENS ; 
 int /*<<< orphan*/  TWL_MODULE_MAIN_CHARGE ; 
 int* twl4030_therm_tbl ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030battery_temperature(int raw_volt)
{
	u8 val;
	int temp, curr, volt, res, ret;

	volt = (raw_volt * TEMP_STEP_SIZE) / TEMP_PSR_R;
	/* Getting and calculating the supply current in micro amperes */
	ret = twl_i2c_read_u8(TWL_MODULE_MAIN_CHARGE, &val,
		REG_BCICTL2);
	if (ret < 0)
		return ret;

	curr = ((val & TWL4030_BCI_ITHSENS) + 1) * 10;
	/* Getting and calculating the thermistor resistance in ohms */
	res = volt * 1000 / curr;
	/* calculating temperature */
	for (temp = 58; temp >= 0; temp--) {
		int actual = twl4030_therm_tbl[temp];
		if ((actual - res) >= 0)
			break;
	}

	return temp + 1;
}