#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct env {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ s8 ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 scalar_t__ IREG_LCL_TEMP ; 
 struct env* dev_get_drvdata (struct device*) ; 
 scalar_t__ env_read (struct env*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_temp(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	int temp_nr = to_sensor_dev_attr(attr)->index;
	struct env *p = dev_get_drvdata(dev);
	s8 val;

	val = env_read(p, IREG_LCL_TEMP + temp_nr);
	return sprintf(buf, "%d\n", ((int) val) - 64);
}