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
 int /*<<< orphan*/  TWL6030_GPADC_CTRL_P1 ; 
 int /*<<< orphan*/  TWL6030_GPADC_CTRL_P1_SP1 ; 
 int twl6030_gpadc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_start_conversion(int channel)
{
	return twl6030_gpadc_write(TWL6030_GPADC_CTRL_P1,
					TWL6030_GPADC_CTRL_P1_SP1);
}