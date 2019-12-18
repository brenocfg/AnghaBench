#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sysfs_entry {int type; int /*<<< orphan*/  attr; scalar_t__ name; } ;
struct qla_hw_data {int beacon_blink_led; TYPE_2__* isp_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct Scsi_Host {TYPE_1__ shost_gendev; } ;
struct TYPE_8__ {struct qla_hw_data* hw; struct Scsi_Host* host; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* beacon_off ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA25XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA27XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA28XX (struct qla_hw_data*) ; 
 struct sysfs_entry* bin_file_entries ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
qla2x00_free_sysfs_attr(scsi_qla_host_t *vha, bool stop_beacon)
{
	struct Scsi_Host *host = vha->host;
	struct sysfs_entry *iter;
	struct qla_hw_data *ha = vha->hw;

	for (iter = bin_file_entries; iter->name; iter++) {
		if (iter->type && !IS_FWI2_CAPABLE(ha))
			continue;
		if (iter->type == 2 && !IS_QLA25XX(ha))
			continue;
		if (iter->type == 3 && !(IS_CNA_CAPABLE(ha)))
			continue;
		if (iter->type == 0x27 &&
		    (!IS_QLA27XX(ha) || !IS_QLA28XX(ha)))
			continue;

		sysfs_remove_bin_file(&host->shost_gendev.kobj,
		    iter->attr);
	}

	if (stop_beacon && ha->beacon_blink_led == 1)
		ha->isp_ops->beacon_off(vha);
}