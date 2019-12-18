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
struct i2c_child_t {unsigned char voltage_mask; } ;

/* Variables and functions */
 unsigned char ENVCTRL_POWERSUPPLY_BAD ; 
 unsigned char ENVCTRL_VOLTAGE_BAD ; 
 unsigned char ENVCTRL_VOLTAGE_POWERSUPPLY_BAD ; 
 unsigned char ENVCTRL_VOLTAGE_POWERSUPPLY_GOOD ; 
 int PCF8584_MAX_CHANNELS ; 
 int* chnls_mask ; 

__attribute__((used)) static unsigned char envctrl_i2c_voltage_status(struct i2c_child_t *pchild,
						unsigned char data,
						char *bufdata)
{
	unsigned char tmp, ret = 0;
	int i, j = 0;

	tmp = data & pchild->voltage_mask;

	/* Two channels are used to monitor voltage and power supply. */
	if (tmp == pchild->voltage_mask) {
		/* All bits are on. Voltage and power supply are okay. */
		ret = ENVCTRL_VOLTAGE_POWERSUPPLY_GOOD;
	} else if (tmp == 0) {
		/* All bits are off. Voltage and power supply are bad */
		ret = ENVCTRL_VOLTAGE_POWERSUPPLY_BAD;
	} else {
		/* Either voltage or power supply has problem. */
		for (i = 0; i < PCF8584_MAX_CHANNELS; i++) {
			if (pchild->voltage_mask & chnls_mask[i]) {
				j++;

				/* Break out when there is a mismatch. */
				if (!(chnls_mask[i] & tmp))
					break; 
			}
		}

		/* Make a wish that hardware will always use the
		 * first channel for voltage and the second for
		 * power supply.
		 */
		if (j == 1)
			ret = ENVCTRL_VOLTAGE_BAD;
		else
			ret = ENVCTRL_POWERSUPPLY_BAD;
	}

	bufdata[0] = ret;
	return 1;
}