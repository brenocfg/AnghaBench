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
struct ds2780_device_info {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  DS2780_TEMP_MSB_REG ; 
 int ds2780_read16 (struct ds2780_device_info*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds2780_get_temperature(struct ds2780_device_info *dev_info,
	int *temperature)
{
	int ret;
	s16 temperature_raw;

	/*
	 * The temperature value is located in 10 bits across the temperature
	 * MSB and LSB registers in two's compliment form
	 * Sign bit of the temperature value is in bit 7 of the temperature
	 * MSB register
	 * Bits 9 - 3 of the temperature value are in bits 6 - 0 of the
	 * temperature MSB register
	 * Bits 2 - 0 of the temperature value are in bits 7 - 5 of the
	 * temperature LSB register
	 */
	ret = ds2780_read16(dev_info, &temperature_raw,
				DS2780_TEMP_MSB_REG);
	if (ret < 0)
		return ret;

	/*
	 * Temperature is measured in units of 0.125 degrees celcius, the
	 * power_supply class measures temperature in tenths of degrees
	 * celsius. The temperature value is stored as a 10 bit number, plus
	 * sign in the upper bits of a 16 bit register.
	 */
	*temperature = ((temperature_raw / 32) * 125) / 100;
	return 0;
}