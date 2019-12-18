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
struct lpfc_vport {scalar_t__ port_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct Scsi_Host {TYPE_1__ shost_dev; } ;

/* Variables and functions */
 scalar_t__ LPFC_NPIV_PORT ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_ctlreg_attr ; 
 int /*<<< orphan*/  sysfs_drvr_stat_data_attr ; 
 int /*<<< orphan*/  sysfs_mbox_attr ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
lpfc_alloc_sysfs_attr(struct lpfc_vport *vport)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	int error;

	error = sysfs_create_bin_file(&shost->shost_dev.kobj,
				      &sysfs_drvr_stat_data_attr);

	/* Virtual ports do not need ctrl_reg and mbox */
	if (error || vport->port_type == LPFC_NPIV_PORT)
		goto out;

	error = sysfs_create_bin_file(&shost->shost_dev.kobj,
				      &sysfs_ctlreg_attr);
	if (error)
		goto out_remove_stat_attr;

	error = sysfs_create_bin_file(&shost->shost_dev.kobj,
				      &sysfs_mbox_attr);
	if (error)
		goto out_remove_ctlreg_attr;

	return 0;
out_remove_ctlreg_attr:
	sysfs_remove_bin_file(&shost->shost_dev.kobj, &sysfs_ctlreg_attr);
out_remove_stat_attr:
	sysfs_remove_bin_file(&shost->shost_dev.kobj,
			&sysfs_drvr_stat_data_attr);
out:
	return error;
}