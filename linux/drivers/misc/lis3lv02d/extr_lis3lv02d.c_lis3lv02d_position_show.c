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
struct lis3lv02d {int /*<<< orphan*/  mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct lis3lv02d* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  lis3lv02d_get_xyz (struct lis3lv02d*,int*,int*,int*) ; 
 int /*<<< orphan*/  lis3lv02d_sysfs_poweron (struct lis3lv02d*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static ssize_t lis3lv02d_position_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct lis3lv02d *lis3 = dev_get_drvdata(dev);
	int x, y, z;

	lis3lv02d_sysfs_poweron(lis3);
	mutex_lock(&lis3->mutex);
	lis3lv02d_get_xyz(lis3, &x, &y, &z);
	mutex_unlock(&lis3->mutex);
	return sprintf(buf, "(%d,%d,%d)\n", x, y, z);
}