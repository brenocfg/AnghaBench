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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 max31785_scale_pwm(u32 sensor_val)
{
	/*
	 * The datasheet describes the accepted value range for manual PWM as
	 * [0, 0x2710], while the hwmon pwmX sysfs interface accepts values in
	 * [0, 255]. The MAX31785 uses DIRECT mode to scale the FAN_COMMAND
	 * registers and in PWM mode the coefficients are m=1, b=0, R=2. The
	 * important observation here is that 0x2710 == 10000 == 100 * 100.
	 *
	 * R=2 (== 10^2 == 100) accounts for scaling the value provided at the
	 * sysfs interface into the required hardware resolution, but it does
	 * not yet yield a value that we can write to the device (this initial
	 * scaling is handled by pmbus_data2reg()). Multiplying by 100 below
	 * translates the parameter value into the percentage units required by
	 * PMBus, and then we scale back by 255 as required by the hwmon pwmX
	 * interface to yield the percentage value at the appropriate
	 * resolution for hardware.
	 */
	return (sensor_val * 100) / 255;
}