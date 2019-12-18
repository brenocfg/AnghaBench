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
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct asus_wmi {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_THERMAL_CTRL ; 
 int DECI_KELVIN_TO_CELSIUS (int) ; 
 int asus_wmi_get_devstate (struct asus_wmi*,int /*<<< orphan*/ ,int*) ; 
 struct asus_wmi* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t asus_hwmon_temp1(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct asus_wmi *asus = dev_get_drvdata(dev);
	u32 value;
	int err;

	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_THERMAL_CTRL, &value);
	if (err < 0)
		return err;

	value = DECI_KELVIN_TO_CELSIUS((value & 0xFFFF)) * 1000;

	return sprintf(buf, "%d\n", value);
}