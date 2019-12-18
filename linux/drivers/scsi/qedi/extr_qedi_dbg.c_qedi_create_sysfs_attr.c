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
struct sysfs_bin_attrs {scalar_t__ name; int /*<<< orphan*/  attr; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct Scsi_Host {TYPE_1__ shost_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,scalar_t__,int) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
qedi_create_sysfs_attr(struct Scsi_Host *shost, struct sysfs_bin_attrs *iter)
{
	int ret = 0;

	for (; iter->name; iter++) {
		ret = sysfs_create_bin_file(&shost->shost_gendev.kobj,
					    iter->attr);
		if (ret)
			pr_err("Unable to create sysfs %s attr, err(%d).\n",
			       iter->name, ret);
	}
	return ret;
}