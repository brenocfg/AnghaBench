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
struct scsi_cmnd {int dummy; } ;
struct sas_ssp_task {struct scsi_cmnd* cmd; } ;
struct sas_task {int /*<<< orphan*/  data_dir; struct sas_ssp_task ssp_task; } ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_prot_sglist (struct scsi_cmnd*) ; 

__attribute__((used)) static void hisi_sas_dif_dma_unmap(struct hisi_hba *hisi_hba,
				   struct sas_task *task, int n_elem_dif)
{
	struct device *dev = hisi_hba->dev;

	if (n_elem_dif) {
		struct sas_ssp_task *ssp_task = &task->ssp_task;
		struct scsi_cmnd *scsi_cmnd = ssp_task->cmd;

		dma_unmap_sg(dev, scsi_prot_sglist(scsi_cmnd),
			     scsi_prot_sg_count(scsi_cmnd),
			     task->data_dir);
	}
}