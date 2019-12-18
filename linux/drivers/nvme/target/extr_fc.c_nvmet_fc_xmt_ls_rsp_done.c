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
struct nvmet_fc_tgtport {int /*<<< orphan*/  dev; } ;
struct nvmet_fc_ls_iod {int /*<<< orphan*/  rspdma; struct nvmet_fc_tgtport* tgtport; } ;
struct nvmefc_tgt_ls_req {struct nvmet_fc_ls_iod* nvmet_fc_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  NVME_FC_MAX_LS_BUFFER_SIZE ; 
 int /*<<< orphan*/  fc_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_fc_free_ls_iod (struct nvmet_fc_tgtport*,struct nvmet_fc_ls_iod*) ; 
 int /*<<< orphan*/  nvmet_fc_tgtport_put (struct nvmet_fc_tgtport*) ; 

__attribute__((used)) static void
nvmet_fc_xmt_ls_rsp_done(struct nvmefc_tgt_ls_req *lsreq)
{
	struct nvmet_fc_ls_iod *iod = lsreq->nvmet_fc_private;
	struct nvmet_fc_tgtport *tgtport = iod->tgtport;

	fc_dma_sync_single_for_cpu(tgtport->dev, iod->rspdma,
				NVME_FC_MAX_LS_BUFFER_SIZE, DMA_TO_DEVICE);
	nvmet_fc_free_ls_iod(tgtport, iod);
	nvmet_fc_tgtport_put(tgtport);
}