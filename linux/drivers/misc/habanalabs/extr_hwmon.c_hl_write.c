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
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {int dummy; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct hl_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 int /*<<< orphan*/  hl_set_pwm_info (struct hl_device*,int,int /*<<< orphan*/ ,long) ; 
#define  hwmon_pwm 130 
#define  hwmon_pwm_enable 129 
#define  hwmon_pwm_input 128 

__attribute__((used)) static int hl_write(struct device *dev, enum hwmon_sensor_types type,
			u32 attr, int channel, long val)
{
	struct hl_device *hdev = dev_get_drvdata(dev);

	if (hl_device_disabled_or_in_reset(hdev))
		return -ENODEV;

	switch (type) {
	case hwmon_pwm:
		switch (attr) {
		case hwmon_pwm_input:
		case hwmon_pwm_enable:
			break;
		default:
			return -EINVAL;
		}
		hl_set_pwm_info(hdev, channel, attr, val);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}