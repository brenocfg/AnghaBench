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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARN (char*) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_activity_done (struct i2c_adapter*) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_configure (struct i2c_adapter*) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_enable (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_set_clock (struct i2c_adapter*) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_set_clock_gating (struct i2c_adapter*,int) ; 

__attribute__((used)) static void smu_v11_0_i2c_init(struct i2c_adapter *control)
{
	/* Disable clock gating */
	smu_v11_0_i2c_set_clock_gating(control, false);

	if (!smu_v11_0_i2c_activity_done(control))
		DRM_WARN("I2C busy !");

	/* Disable I2C */
	smu_v11_0_i2c_enable(control, false);

	/* Configure I2C to operate as master and in standard mode */
	smu_v11_0_i2c_configure(control);

	/* Initialize the clock to 50 kHz default */
	smu_v11_0_i2c_set_clock(control);

}