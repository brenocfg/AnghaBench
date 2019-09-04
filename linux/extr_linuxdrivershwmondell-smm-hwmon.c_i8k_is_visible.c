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
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int I8K_HWMON_HAVE_FAN1 ; 
 int I8K_HWMON_HAVE_FAN2 ; 
 int I8K_HWMON_HAVE_FAN3 ; 
 int I8K_HWMON_HAVE_TEMP1 ; 
 int I8K_HWMON_HAVE_TEMP2 ; 
 int I8K_HWMON_HAVE_TEMP3 ; 
 int I8K_HWMON_HAVE_TEMP4 ; 
 scalar_t__ disallow_fan_support ; 
 scalar_t__ disallow_fan_type_call ; 
 int i8k_hwmon_flags ; 

__attribute__((used)) static umode_t i8k_is_visible(struct kobject *kobj, struct attribute *attr,
			      int index)
{
	if (disallow_fan_support && index >= 8)
		return 0;
	if (disallow_fan_type_call &&
	    (index == 9 || index == 12 || index == 15))
		return 0;
	if (index >= 0 && index <= 1 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP1))
		return 0;
	if (index >= 2 && index <= 3 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP2))
		return 0;
	if (index >= 4 && index <= 5 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP3))
		return 0;
	if (index >= 6 && index <= 7 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_TEMP4))
		return 0;
	if (index >= 8 && index <= 10 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_FAN1))
		return 0;
	if (index >= 11 && index <= 13 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_FAN2))
		return 0;
	if (index >= 14 && index <= 16 &&
	    !(i8k_hwmon_flags & I8K_HWMON_HAVE_FAN3))
		return 0;

	return attr->mode;
}