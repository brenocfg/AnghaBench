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
 int /*<<< orphan*/  DS2780_VOLT_MSB_REG ; 
 int ds2780_read16 (struct ds2780_device_info*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds2780_get_voltage(struct ds2780_device_info *dev_info,
	int *voltage_uV)
{
	int ret;
	s16 voltage_raw;

	/*
	 * The voltage value is located in 10 bits across the voltage MSB
	 * and LSB registers in two's compliment form
	 * Sign bit of the voltage value is in bit 7 of the voltage MSB register
	 * Bits 9 - 3 of the voltage value are in bits 6 - 0 of the
	 * voltage MSB register
	 * Bits 2 - 0 of the voltage value are in bits 7 - 5 of the
	 * voltage LSB register
	 */
	ret = ds2780_read16(dev_info, &voltage_raw,
				DS2780_VOLT_MSB_REG);
	if (ret < 0)
		return ret;

	/*
	 * DS2780 reports voltage in units of 4.88mV, but the battery class
	 * reports in units of uV, so convert by multiplying by 4880.
	 */
	*voltage_uV = (voltage_raw / 32) * 4880;
	return 0;
}