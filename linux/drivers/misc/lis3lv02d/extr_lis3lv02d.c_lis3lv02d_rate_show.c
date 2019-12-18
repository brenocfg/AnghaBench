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
struct lis3lv02d {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct lis3lv02d* dev_get_drvdata (struct device*) ; 
 int lis3lv02d_get_odr (struct lis3lv02d*) ; 
 int /*<<< orphan*/  lis3lv02d_sysfs_poweron (struct lis3lv02d*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t lis3lv02d_rate_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct lis3lv02d *lis3 = dev_get_drvdata(dev);

	lis3lv02d_sysfs_poweron(lis3);
	return sprintf(buf, "%d\n", lis3lv02d_get_odr(lis3));
}