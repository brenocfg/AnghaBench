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
 unsigned int PIN_CONFIG_SLEEP_HARDWARE_STATE ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static bool sprd_pinctrl_check_sleep_config(unsigned long *configs,
					    unsigned int num_configs)
{
	unsigned int param;
	int i;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		if (param == PIN_CONFIG_SLEEP_HARDWARE_STATE)
			return true;
	}

	return false;
}