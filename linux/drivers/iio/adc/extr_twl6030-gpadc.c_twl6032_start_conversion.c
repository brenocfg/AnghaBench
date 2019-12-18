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

/* Variables and functions */
 int TWL6030_GPADC_CTRL_P1_SP1 ; 
 int /*<<< orphan*/  TWL6032_GPADC_CTRL_P1 ; 
 int /*<<< orphan*/  TWL6032_GPADC_GPSELECT_ISB ; 
 int twl6030_gpadc_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int twl6032_start_conversion(int channel)
{
	int ret;

	ret = twl6030_gpadc_write(TWL6032_GPADC_GPSELECT_ISB, channel);
	if (ret)
		return ret;

	return twl6030_gpadc_write(TWL6032_GPADC_CTRL_P1,
						TWL6030_GPADC_CTRL_P1_SP1);
}