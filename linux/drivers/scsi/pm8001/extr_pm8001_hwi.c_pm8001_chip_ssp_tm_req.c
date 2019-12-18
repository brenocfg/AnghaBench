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
struct ssp_ini_tm_start_req {int ds_ads_m; void* tag; int /*<<< orphan*/  lun; void* tmf; void* relate_tag; void* device_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  LUN; } ;
struct sas_task {TYPE_1__ ssp_task; struct domain_device* dev; } ;
struct pm8001_tmf_task {int /*<<< orphan*/  tmf; int /*<<< orphan*/  tag_of_task_to_be_managed; } ;
struct pm8001_hba_info {scalar_t__ chip_id; struct inbound_queue_table* inbnd_q_tbl; } ;
struct pm8001_device {int /*<<< orphan*/  device_id; } ;
struct pm8001_ccb_info {int /*<<< orphan*/  ccb_tag; struct sas_task* task; } ;
struct inbound_queue_table {int dummy; } ;
struct domain_device {struct pm8001_device* lldd_dev; } ;
typedef  int /*<<< orphan*/  sspTMCmd ;

/* Variables and functions */
 int /*<<< orphan*/  OPC_INB_SSPINITMSTART ; 
 scalar_t__ chip_8001 ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ssp_ini_tm_start_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,int /*<<< orphan*/ ,struct ssp_ini_tm_start_req*,int /*<<< orphan*/ ) ; 

int pm8001_chip_ssp_tm_req(struct pm8001_hba_info *pm8001_ha,
	struct pm8001_ccb_info *ccb, struct pm8001_tmf_task *tmf)
{
	struct sas_task *task = ccb->task;
	struct domain_device *dev = task->dev;
	struct pm8001_device *pm8001_dev = dev->lldd_dev;
	u32 opc = OPC_INB_SSPINITMSTART;
	struct inbound_queue_table *circularQ;
	struct ssp_ini_tm_start_req sspTMCmd;
	int ret;

	memset(&sspTMCmd, 0, sizeof(sspTMCmd));
	sspTMCmd.device_id = cpu_to_le32(pm8001_dev->device_id);
	sspTMCmd.relate_tag = cpu_to_le32(tmf->tag_of_task_to_be_managed);
	sspTMCmd.tmf = cpu_to_le32(tmf->tmf);
	memcpy(sspTMCmd.lun, task->ssp_task.LUN, 8);
	sspTMCmd.tag = cpu_to_le32(ccb->ccb_tag);
	if (pm8001_ha->chip_id != chip_8001)
		sspTMCmd.ds_ads_m = 0x08;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &sspTMCmd, 0);
	return ret;
}