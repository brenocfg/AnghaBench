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
typedef  int /*<<< orphan*/  u32 ;
struct scsi_lun {int /*<<< orphan*/  scsi_lun; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct sas_task {int task_proto; struct hisi_sas_slot* lldd_task; struct domain_device* dev; struct scsi_cmnd* uldd_task; } ;
struct hisi_sas_tmf_task {int /*<<< orphan*/  tag_of_task_to_be_managed; int /*<<< orphan*/  tmf; } ;
struct hisi_sas_slot {int /*<<< orphan*/  idx; } ;
struct domain_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int SAS_PROTOCOL_SSP ; 
 int /*<<< orphan*/  TMF_QUERY_TASK ; 
#define  TMF_RESP_FUNC_COMPLETE 130 
#define  TMF_RESP_FUNC_FAILED 129 
#define  TMF_RESP_FUNC_SUCC 128 
 int hisi_sas_debug_issue_ssp_tmf (struct domain_device*,int /*<<< orphan*/ ,struct hisi_sas_tmf_task*) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 

__attribute__((used)) static int hisi_sas_query_task(struct sas_task *task)
{
	struct scsi_lun lun;
	struct hisi_sas_tmf_task tmf_task;
	int rc = TMF_RESP_FUNC_FAILED;

	if (task->lldd_task && task->task_proto & SAS_PROTOCOL_SSP) {
		struct scsi_cmnd *cmnd = task->uldd_task;
		struct domain_device *device = task->dev;
		struct hisi_sas_slot *slot = task->lldd_task;
		u32 tag = slot->idx;

		int_to_scsilun(cmnd->device->lun, &lun);
		tmf_task.tmf = TMF_QUERY_TASK;
		tmf_task.tag_of_task_to_be_managed = tag;

		rc = hisi_sas_debug_issue_ssp_tmf(device,
						  lun.scsi_lun,
						  &tmf_task);
		switch (rc) {
		/* The task is still in Lun, release it then */
		case TMF_RESP_FUNC_SUCC:
		/* The task is not in Lun or failed, reset the phy */
		case TMF_RESP_FUNC_FAILED:
		case TMF_RESP_FUNC_COMPLETE:
			break;
		default:
			rc = TMF_RESP_FUNC_FAILED;
			break;
		}
	}
	return rc;
}