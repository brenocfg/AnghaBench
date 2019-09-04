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
typedef  int s32 ;

/* Variables and functions */
 int nsa320_hwmon_update (struct device*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t temp1_input_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	s32 mcu_data = nsa320_hwmon_update(dev);

	if (mcu_data < 0)
		return mcu_data;

	return sprintf(buf, "%d\n", (mcu_data & 0xffff) * 100);
}