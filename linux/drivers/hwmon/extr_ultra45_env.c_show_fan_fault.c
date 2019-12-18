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
typedef  int u8 ;
struct env {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  IREG_FAN_STAT ; 
 struct env* dev_get_drvdata (struct device*) ; 
 int env_read (struct env*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_fan_fault(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	int fan_nr = to_sensor_dev_attr(attr)->index;
	struct env *p = dev_get_drvdata(dev);
	u8 val = env_read(p, IREG_FAN_STAT);
	return sprintf(buf, "%d\n", (val & (1 << fan_nr)) ? 1 : 0);
}