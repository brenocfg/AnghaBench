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
struct ipr_sglist {int /*<<< orphan*/  num_sg; int /*<<< orphan*/  scatterlist; } ;
struct ipr_ioa_cfg {TYPE_1__* pdev; struct ipr_sglist* ucode_sglist; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int IPR_RC_JOB_CONTINUE ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_reset_alert ; 

__attribute__((used)) static int ipr_reset_ucode_download_done(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	struct ipr_sglist *sglist = ioa_cfg->ucode_sglist;

	dma_unmap_sg(&ioa_cfg->pdev->dev, sglist->scatterlist,
		     sglist->num_sg, DMA_TO_DEVICE);

	ipr_cmd->job_step = ipr_reset_alert;
	return IPR_RC_JOB_CONTINUE;
}