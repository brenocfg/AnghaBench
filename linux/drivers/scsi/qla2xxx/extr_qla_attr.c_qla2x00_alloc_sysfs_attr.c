#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sysfs_entry {int type; scalar_t__ name; int /*<<< orphan*/  attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct Scsi_Host {TYPE_1__ shost_gendev; } ;
struct TYPE_7__ {int /*<<< orphan*/  hw; struct Scsi_Host* host; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_CNA_CAPABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_FWI2_CAPABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_QLA25XX (int /*<<< orphan*/ ) ; 
 struct sysfs_entry* bin_file_entries ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
qla2x00_alloc_sysfs_attr(scsi_qla_host_t *vha)
{
	struct Scsi_Host *host = vha->host;
	struct sysfs_entry *iter;
	int ret;

	for (iter = bin_file_entries; iter->name; iter++) {
		if (iter->type && !IS_FWI2_CAPABLE(vha->hw))
			continue;
		if (iter->type == 2 && !IS_QLA25XX(vha->hw))
			continue;
		if (iter->type == 3 && !(IS_CNA_CAPABLE(vha->hw)))
			continue;

		ret = sysfs_create_bin_file(&host->shost_gendev.kobj,
		    iter->attr);
		if (ret)
			ql_log(ql_log_warn, vha, 0x00f3,
			    "Unable to create sysfs %s binary attribute (%d).\n",
			    iter->name, ret);
		else
			ql_dbg(ql_dbg_init, vha, 0x00f4,
			    "Successfully created sysfs %s binary attribute.\n",
			    iter->name);
	}
}