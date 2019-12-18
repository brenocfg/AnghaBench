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
struct nvmet_fc_tgtport {struct nvmet_fc_ls_iod* iod; int /*<<< orphan*/  dev; } ;
struct nvmet_fc_ls_iod {int /*<<< orphan*/  ls_list; struct nvmet_fc_ls_iod* rqstbuf; int /*<<< orphan*/  rspdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int NVMET_LS_CTX_COUNT ; 
 int /*<<< orphan*/  NVME_FC_MAX_LS_BUFFER_SIZE ; 
 int /*<<< orphan*/  fc_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvmet_fc_ls_iod*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvmet_fc_free_ls_iodlist(struct nvmet_fc_tgtport *tgtport)
{
	struct nvmet_fc_ls_iod *iod = tgtport->iod;
	int i;

	for (i = 0; i < NVMET_LS_CTX_COUNT; iod++, i++) {
		fc_dma_unmap_single(tgtport->dev,
				iod->rspdma, NVME_FC_MAX_LS_BUFFER_SIZE,
				DMA_TO_DEVICE);
		kfree(iod->rqstbuf);
		list_del(&iod->ls_list);
	}
	kfree(tgtport->iod);
}