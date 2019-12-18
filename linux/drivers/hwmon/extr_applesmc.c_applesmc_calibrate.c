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
 int /*<<< orphan*/  MOTION_SENSOR_X_KEY ; 
 int /*<<< orphan*/  MOTION_SENSOR_Y_KEY ; 
 int /*<<< orphan*/  applesmc_read_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rest_x ; 
 int /*<<< orphan*/  rest_y ; 

__attribute__((used)) static void applesmc_calibrate(void)
{
	applesmc_read_s16(MOTION_SENSOR_X_KEY, &rest_x);
	applesmc_read_s16(MOTION_SENSOR_Y_KEY, &rest_y);
	rest_x = -rest_x;
}