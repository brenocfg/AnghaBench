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
 int ENODATA ; 
 int I8K_MAX_TEMP ; 
 int _i8k_get_temp (int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int i8k_get_temp(int sensor)
{
	int temp = _i8k_get_temp(sensor);

	/*
	 * Sometimes the temperature sensor returns 0x99, which is out of range.
	 * In this case we retry (once) before returning an error.
	 # 1003655137 00000058 00005a4b
	 # 1003655138 00000099 00003a80 <--- 0x99 = 153 degrees
	 # 1003655139 00000054 00005c52
	 */
	if (temp == 0x99) {
		msleep(100);
		temp = _i8k_get_temp(sensor);
	}
	/*
	 * Return -ENODATA for all invalid temperatures.
	 *
	 * Known instances are the 0x99 value as seen above as well as
	 * 0xc1 (193), which may be returned when trying to read the GPU
	 * temperature if the system supports a GPU and it is currently
	 * turned off.
	 */
	if (temp > I8K_MAX_TEMP)
		return -ENODATA;

	return temp;
}