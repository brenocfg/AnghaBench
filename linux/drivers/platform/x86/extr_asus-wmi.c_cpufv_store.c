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
 int /*<<< orphan*/  ASUS_WMI_METHODID_CFVS ; 
 int EINVAL ; 
 int asus_wmi_evaluate_method (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t cpufv_store(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	int value, rv;

	rv = kstrtoint(buf, 0, &value);
	if (rv)
		return rv;

	if (value < 0 || value > 2)
		return -EINVAL;

	rv = asus_wmi_evaluate_method(ASUS_WMI_METHODID_CFVS, value, 0, NULL);
	if (rv < 0)
		return rv;

	return count;
}