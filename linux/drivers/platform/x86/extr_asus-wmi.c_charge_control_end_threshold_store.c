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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_RSOC ; 
 int EINVAL ; 
 int EIO ; 
 int asus_wmi_set_devstate (int /*<<< orphan*/ ,int,int*) ; 
 int charge_end_threshold ; 
 int kstrtouint (char const*,int,int*) ; 

__attribute__((used)) static ssize_t charge_control_end_threshold_store(struct device *dev,
						  struct device_attribute *attr,
						  const char *buf, size_t count)
{
	int value, ret, rv;

	ret = kstrtouint(buf, 10, &value);
	if (ret)
		return ret;

	if (value < 0 || value > 100)
		return -EINVAL;

	ret = asus_wmi_set_devstate(ASUS_WMI_DEVID_RSOC, value, &rv);
	if (ret)
		return ret;

	if (rv != 1)
		return -EIO;

	/* There isn't any method in the DSDT to read the threshold, so we
	 * save the threshold.
	 */
	charge_end_threshold = value;
	return count;
}