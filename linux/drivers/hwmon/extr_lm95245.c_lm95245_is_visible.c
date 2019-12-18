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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
#define  hwmon_chip 130 
#define  hwmon_chip_update_interval 129 
#define  hwmon_temp 128 
 int lm95245_temp_is_visible (void const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static umode_t lm95245_is_visible(const void *data,
				  enum hwmon_sensor_types type,
				  u32 attr, int channel)
{
	switch (type) {
	case hwmon_chip:
		switch (attr) {
		case hwmon_chip_update_interval:
			return 0644;
		default:
			return 0;
		}
	case hwmon_temp:
		return lm95245_temp_is_visible(data, attr, channel);
	default:
		return 0;
	}
}