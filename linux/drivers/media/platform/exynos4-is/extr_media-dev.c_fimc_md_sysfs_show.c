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
struct fimc_md {scalar_t__ user_subdev_api; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct fimc_md* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  strscpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t fimc_md_sysfs_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct fimc_md *fmd = dev_get_drvdata(dev);

	if (fmd->user_subdev_api)
		return strscpy(buf, "Sub-device API (sub-dev)\n", PAGE_SIZE);

	return strscpy(buf, "V4L2 video node only API (vid-dev)\n", PAGE_SIZE);
}