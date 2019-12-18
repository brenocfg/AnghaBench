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
struct nvmet_fc_tgtport {int /*<<< orphan*/  fc_target_port; TYPE_1__* ops; int /*<<< orphan*/  dev; } ;
struct nvmet_fc_ls_iod {int /*<<< orphan*/  lsreq; int /*<<< orphan*/  rspdma; } ;
struct TYPE_2__ {int (* xmt_ls_rsp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  NVME_FC_MAX_LS_BUFFER_SIZE ; 
 int /*<<< orphan*/  fc_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_fc_xmt_ls_rsp_done (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvmet_fc_xmt_ls_rsp(struct nvmet_fc_tgtport *tgtport,
				struct nvmet_fc_ls_iod *iod)
{
	int ret;

	fc_dma_sync_single_for_device(tgtport->dev, iod->rspdma,
				  NVME_FC_MAX_LS_BUFFER_SIZE, DMA_TO_DEVICE);

	ret = tgtport->ops->xmt_ls_rsp(&tgtport->fc_target_port, iod->lsreq);
	if (ret)
		nvmet_fc_xmt_ls_rsp_done(iod->lsreq);
}