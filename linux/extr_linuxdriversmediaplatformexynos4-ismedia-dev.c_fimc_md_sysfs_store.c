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
struct fimc_md {int user_subdev_api; TYPE_2__** fimc; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {int user_subdev_api; } ;
struct TYPE_4__ {TYPE_1__ vid_cap; } ;

/* Variables and functions */
 int FIMC_MAX_DEVS ; 
 struct fimc_md* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static ssize_t fimc_md_sysfs_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct fimc_md *fmd = dev_get_drvdata(dev);
	bool subdev_api;
	int i;

	if (!strcmp(buf, "vid-dev\n"))
		subdev_api = false;
	else if (!strcmp(buf, "sub-dev\n"))
		subdev_api = true;
	else
		return count;

	fmd->user_subdev_api = subdev_api;
	for (i = 0; i < FIMC_MAX_DEVS; i++)
		if (fmd->fimc[i])
			fmd->fimc[i]->vid_cap.user_subdev_api = subdev_api;
	return count;
}