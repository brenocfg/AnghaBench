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
typedef  int u16 ;
struct ad5820_device {int focus_absolute; scalar_t__ standby; scalar_t__ focus_ramp_mode; int /*<<< orphan*/  focus_ramp_time; } ;

/* Variables and functions */
 int AD5820_DAC_SHIFT ; 
 int AD5820_POWER_DOWN ; 
 int AD5820_RAMP_MODE_64_16 ; 
 int AD5820_RAMP_MODE_LINEAR ; 
 int RAMP_US_TO_CODE (int /*<<< orphan*/ ) ; 
 int ad5820_write (struct ad5820_device*,int) ; 

__attribute__((used)) static int ad5820_update_hw(struct ad5820_device *coil)
{
	u16 status;

	status = RAMP_US_TO_CODE(coil->focus_ramp_time);
	status |= coil->focus_ramp_mode
		? AD5820_RAMP_MODE_64_16 : AD5820_RAMP_MODE_LINEAR;
	status |= coil->focus_absolute << AD5820_DAC_SHIFT;

	if (coil->standby)
		status |= AD5820_POWER_DOWN;

	return ad5820_write(coil, status);
}