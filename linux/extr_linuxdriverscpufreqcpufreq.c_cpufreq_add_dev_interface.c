#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct freq_attr {int /*<<< orphan*/  attr; } ;
struct cpufreq_policy {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {int /*<<< orphan*/  attr; } ;
struct TYPE_7__ {scalar_t__ bios_limit; scalar_t__ get; struct freq_attr** attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  attr; } ;
struct TYPE_5__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 TYPE_4__ bios_limit ; 
 TYPE_3__* cpufreq_driver ; 
 TYPE_2__ cpuinfo_cur_freq ; 
 TYPE_1__ scaling_cur_freq ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpufreq_add_dev_interface(struct cpufreq_policy *policy)
{
	struct freq_attr **drv_attr;
	int ret = 0;

	/* set up files for this cpu device */
	drv_attr = cpufreq_driver->attr;
	while (drv_attr && *drv_attr) {
		ret = sysfs_create_file(&policy->kobj, &((*drv_attr)->attr));
		if (ret)
			return ret;
		drv_attr++;
	}
	if (cpufreq_driver->get) {
		ret = sysfs_create_file(&policy->kobj, &cpuinfo_cur_freq.attr);
		if (ret)
			return ret;
	}

	ret = sysfs_create_file(&policy->kobj, &scaling_cur_freq.attr);
	if (ret)
		return ret;

	if (cpufreq_driver->bios_limit) {
		ret = sysfs_create_file(&policy->kobj, &bios_limit.attr);
		if (ret)
			return ret;
	}

	return 0;
}