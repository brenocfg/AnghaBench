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
struct asus_wmi {scalar_t__ agfn_pwm; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_FAN_CTRL ; 
 int asus_wmi_get_devstate (struct asus_wmi*,int /*<<< orphan*/ ,int*) ; 
 struct asus_wmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t pwm1_show(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	struct asus_wmi *asus = dev_get_drvdata(dev);
	int err;
	int value;

	/* If we already set a value then just return it */
	if (asus->agfn_pwm >= 0)
		return sprintf(buf, "%d\n", asus->agfn_pwm);

	/*
	 * If we haven't set already set a value through the AGFN interface,
	 * we read a current value through the (now-deprecated) FAN_CTRL device.
	 */
	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FAN_CTRL, &value);
	if (err < 0)
		return err;

	value &= 0xFF;

	if (value == 1) /* Low Speed */
		value = 85;
	else if (value == 2)
		value = 170;
	else if (value == 3)
		value = 255;
	else if (value) {
		pr_err("Unknown fan speed %#x\n", value);
		value = -1;
	}

	return sprintf(buf, "%d\n", value);
}