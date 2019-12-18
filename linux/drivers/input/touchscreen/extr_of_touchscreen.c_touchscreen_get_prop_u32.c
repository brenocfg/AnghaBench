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
typedef  unsigned int u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int device_property_read_u32 (struct device*,char const*,unsigned int*) ; 

__attribute__((used)) static bool touchscreen_get_prop_u32(struct device *dev,
				     const char *property,
				     unsigned int default_value,
				     unsigned int *value)
{
	u32 val;
	int error;

	error = device_property_read_u32(dev, property, &val);
	if (error) {
		*value = default_value;
		return false;
	}

	*value = val;
	return true;
}