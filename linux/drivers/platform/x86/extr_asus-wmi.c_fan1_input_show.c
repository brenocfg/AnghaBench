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
struct asus_wmi {int fan_type; int /*<<< orphan*/  fan_pwm_mode; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_FAN_CTRL_MANUAL ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_CPU_FAN_CTRL ; 
 int ENXIO ; 
#define  FAN_TYPE_AGFN 129 
#define  FAN_TYPE_SPEC83 128 
 int asus_agfn_fan_speed_read (struct asus_wmi*,int,int*) ; 
 int asus_wmi_get_devstate (struct asus_wmi*,int /*<<< orphan*/ ,int*) ; 
 struct asus_wmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t fan1_input_show(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct asus_wmi *asus = dev_get_drvdata(dev);
	int value;
	int ret;

	switch (asus->fan_type) {
	case FAN_TYPE_SPEC83:
		ret = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_CPU_FAN_CTRL,
					    &value);
		if (ret < 0)
			return ret;

		value &= 0xffff;
		break;

	case FAN_TYPE_AGFN:
		/* no speed readable on manual mode */
		if (asus->fan_pwm_mode == ASUS_FAN_CTRL_MANUAL)
			return -ENXIO;

		ret = asus_agfn_fan_speed_read(asus, 1, &value);
		if (ret) {
			pr_warn("reading fan speed failed: %d\n", ret);
			return -ENXIO;
		}
		break;

	default:
		return -ENXIO;
	}

	return sprintf(buf, "%d\n", value < 0 ? -1 : value*100);
}