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
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  attr; } ;
struct dev_ext_attribute {TYPE_1__ attr; } ;
struct coresight_device {scalar_t__ type; struct dev_ext_attribute* ea; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ CORESIGHT_DEV_TYPE_LINKSINK ; 
 scalar_t__ CORESIGHT_DEV_TYPE_SINK ; 
 TYPE_2__ etm_pmu ; 
 int /*<<< orphan*/  sysfs_remove_file_from_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void etm_perf_del_symlink_sink(struct coresight_device *csdev)
{
	struct device *pmu_dev = etm_pmu.dev;
	struct dev_ext_attribute *ea = csdev->ea;

	if (csdev->type != CORESIGHT_DEV_TYPE_SINK &&
	    csdev->type != CORESIGHT_DEV_TYPE_LINKSINK)
		return;

	if (!ea)
		return;

	sysfs_remove_file_from_group(&pmu_dev->kobj,
				     &ea->attr.attr, "sinks");
	csdev->ea = NULL;
}