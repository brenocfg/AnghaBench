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
typedef  int umode_t ;
typedef  int u8 ;
typedef  int u32 ;
struct max31790_data {int* fan_config; } ;

/* Variables and functions */
 int MAX31790_FAN_CFG_TACH_INPUT ; 
 int NR_CHANNEL ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
#define  hwmon_fan_fault 130 
#define  hwmon_fan_input 129 
#define  hwmon_fan_target 128 

__attribute__((used)) static umode_t max31790_fan_is_visible(const void *_data, u32 attr, int channel)
{
	const struct max31790_data *data = _data;
	u8 fan_config = data->fan_config[channel % NR_CHANNEL];

	switch (attr) {
	case hwmon_fan_input:
	case hwmon_fan_fault:
		if (channel < NR_CHANNEL ||
		    (fan_config & MAX31790_FAN_CFG_TACH_INPUT))
			return S_IRUGO;
		return 0;
	case hwmon_fan_target:
		if (channel < NR_CHANNEL &&
		    !(fan_config & MAX31790_FAN_CFG_TACH_INPUT))
			return S_IRUGO | S_IWUSR;
		return 0;
	default:
		return 0;
	}
}