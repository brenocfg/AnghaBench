#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ccwgroup_device {TYPE_2__** cdev; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {size_t driver_info; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 char** lcs_type ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 

__attribute__((used)) static ssize_t
lcs_type_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ccwgroup_device *cgdev;

	cgdev = to_ccwgroupdev(dev);
	if (!cgdev)
		return -ENODEV;

	return sprintf(buf, "%s\n", lcs_type[cgdev->cdev[0]->id.driver_info]);
}