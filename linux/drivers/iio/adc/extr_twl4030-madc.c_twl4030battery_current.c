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
 int CURR_PSR_R1 ; 
 int CURR_PSR_R2 ; 
 int CURR_STEP_SIZE ; 
 int /*<<< orphan*/  TWL4030_BCI_BCICTL1 ; 
 int TWL4030_BCI_CGAIN ; 
 int /*<<< orphan*/  TWL_MODULE_MAIN_CHARGE ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030battery_current(int raw_volt)
{
	int ret;
	u8 val;

	ret = twl_i2c_read_u8(TWL_MODULE_MAIN_CHARGE, &val,
		TWL4030_BCI_BCICTL1);
	if (ret)
		return ret;
	if (val & TWL4030_BCI_CGAIN) /* slope of 0.44 mV/mA */
		return (raw_volt * CURR_STEP_SIZE) / CURR_PSR_R1;
	else /* slope of 0.88 mV/mA */
		return (raw_volt * CURR_STEP_SIZE) / CURR_PSR_R2;
}