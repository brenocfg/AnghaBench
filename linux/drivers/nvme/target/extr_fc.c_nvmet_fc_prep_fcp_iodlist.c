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
struct nvmet_fc_tgt_queue {int sqsize; int /*<<< orphan*/  fod_list; struct nvmet_fc_fcp_iod* fod; } ;
struct nvmet_fc_fcp_iod {int active; int abort; int aborted; long rspdma; int /*<<< orphan*/  fcp_list; int /*<<< orphan*/  rspiubuf; int /*<<< orphan*/  flock; int /*<<< orphan*/ * fcpreq; struct nvmet_fc_tgt_queue* queue; struct nvmet_fc_tgtport* tgtport; int /*<<< orphan*/  defer_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long fc_dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fc_dma_mapping_error (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  fc_dma_unmap_single (int /*<<< orphan*/ ,long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_fc_fcp_rqst_op_defer_work ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvmet_fc_prep_fcp_iodlist(struct nvmet_fc_tgtport *tgtport,
				struct nvmet_fc_tgt_queue *queue)
{
	struct nvmet_fc_fcp_iod *fod = queue->fod;
	int i;

	for (i = 0; i < queue->sqsize; fod++, i++) {
		INIT_WORK(&fod->defer_work, nvmet_fc_fcp_rqst_op_defer_work);
		fod->tgtport = tgtport;
		fod->queue = queue;
		fod->active = false;
		fod->abort = false;
		fod->aborted = false;
		fod->fcpreq = NULL;
		list_add_tail(&fod->fcp_list, &queue->fod_list);
		spin_lock_init(&fod->flock);

		fod->rspdma = fc_dma_map_single(tgtport->dev, &fod->rspiubuf,
					sizeof(fod->rspiubuf), DMA_TO_DEVICE);
		if (fc_dma_mapping_error(tgtport->dev, fod->rspdma)) {
			list_del(&fod->fcp_list);
			for (fod--, i--; i >= 0; fod--, i--) {
				fc_dma_unmap_single(tgtport->dev, fod->rspdma,
						sizeof(fod->rspiubuf),
						DMA_TO_DEVICE);
				fod->rspdma = 0L;
				list_del(&fod->fcp_list);
			}

			return;
		}
	}
}