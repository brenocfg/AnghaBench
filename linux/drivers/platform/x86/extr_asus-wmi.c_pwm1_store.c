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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct asus_wmi {int /*<<< orphan*/  fan_pwm_mode; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_FAN_CTRL_MANUAL ; 
 int asus_agfn_fan_speed_write (struct asus_wmi*,int,int*) ; 
 int clamp (int,int /*<<< orphan*/ ,int) ; 
 struct asus_wmi* dev_get_drvdata (struct device*) ; 
 int kstrtouint (char const*,int,int*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static ssize_t pwm1_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count) {
	struct asus_wmi *asus = dev_get_drvdata(dev);
	int value;
	int state;
	int ret;

	ret = kstrtouint(buf, 10, &value);
	if (ret)
		return ret;

	value = clamp(value, 0, 255);

	state = asus_agfn_fan_speed_write(asus, 1, &value);
	if (state)
		pr_warn("Setting fan speed failed: %d\n", state);
	else
		asus->fan_pwm_mode = ASUS_FAN_CTRL_MANUAL;

	return count;
}