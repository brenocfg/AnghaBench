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
struct asus_wmi {int fan_pwm_mode; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct asus_wmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t pwm1_enable_show(struct device *dev,
						 struct device_attribute *attr,
						 char *buf)
{
	struct asus_wmi *asus = dev_get_drvdata(dev);

	/*
	 * Just read back the cached pwm mode.
	 *
	 * For the CPU_FAN device, the spec indicates that we should be
	 * able to read the device status and consult bit 19 to see if we
	 * are in Full On or Automatic mode. However, this does not work
	 * in practice on X532FL at least (the bit is always 0) and there's
	 * also nothing in the DSDT to indicate that this behaviour exists.
	 */
	return sprintf(buf, "%d\n", asus->fan_pwm_mode);
}