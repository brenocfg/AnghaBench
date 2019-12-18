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
 int INPUT_STRING_LEN ; 
#define  PEM_INPUT_POWER_LSB 129 
#define  PEM_INPUT_VOLTAGE 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static long pem_get_input(u8 *data, int len, int index)
{
	long val;

	switch (index) {
	case PEM_INPUT_VOLTAGE:
		if (len == INPUT_STRING_LEN)
			val = (data[index] + (data[index+1] << 8) - 75) * 1000;
		else
			val = (data[index] - 75) * 1000;
		break;
	case PEM_INPUT_POWER_LSB:
		if (len == INPUT_STRING_LEN)
			index++;
		val = (data[index] + (data[index+1] << 8)) * 1000000L;
		break;
	default:
		WARN_ON_ONCE(1);
		val = 0;
	}
	return val;
}