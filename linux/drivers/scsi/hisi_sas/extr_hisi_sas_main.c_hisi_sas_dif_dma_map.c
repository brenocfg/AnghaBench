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
struct sas_task {int /*<<< orphan*/  data_dir; struct sas_ssp_task ssp_task; scalar_t__ num_scatter; } ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int HISI_SAS_SGE_DIF_PAGE_CNT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int dma_map_sg (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_prot_sglist (struct scsi_cmnd*) ; 

__attribute__((used)) static int hisi_sas_dif_dma_map(struct hisi_hba *hisi_hba,
				int *n_elem_dif, struct sas_task *task)
{
	struct device *dev = hisi_hba->dev;
	struct sas_ssp_task *ssp_task;
	struct scsi_cmnd *scsi_cmnd;
	int rc;

	if (task->num_scatter) {
		ssp_task = &task->ssp_task;
		scsi_cmnd = ssp_task->cmd;

		if (scsi_prot_sg_count(scsi_cmnd)) {
			*n_elem_dif = dma_map_sg(dev,
						 scsi_prot_sglist(scsi_cmnd),
						 scsi_prot_sg_count(scsi_cmnd),
						 task->data_dir);

			if (!*n_elem_dif)
				return -ENOMEM;

			if (*n_elem_dif > HISI_SAS_SGE_DIF_PAGE_CNT) {
				dev_err(dev, "task prep: n_elem_dif(%d) too large\n",
					*n_elem_dif);
				rc = -EINVAL;
				goto err_out_dif_dma_unmap;
			}
		}
	}

	return 0;

err_out_dif_dma_unmap:
	dma_unmap_sg(dev, scsi_prot_sglist(scsi_cmnd),
		     scsi_prot_sg_count(scsi_cmnd), task->data_dir);
	return rc;
}