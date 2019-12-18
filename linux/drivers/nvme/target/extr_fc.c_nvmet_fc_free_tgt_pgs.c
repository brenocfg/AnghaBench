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
struct nvmet_fc_fcp_iod {scalar_t__ io_dir; scalar_t__ data_sg_cnt; int /*<<< orphan*/ * data_sg; TYPE_1__* tgtport; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ NVMET_FCP_WRITE ; 
 int /*<<< orphan*/  fc_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgl_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvmet_fc_free_tgt_pgs(struct nvmet_fc_fcp_iod *fod)
{
	if (!fod->data_sg || !fod->data_sg_cnt)
		return;

	fc_dma_unmap_sg(fod->tgtport->dev, fod->data_sg, fod->data_sg_cnt,
				((fod->io_dir == NVMET_FCP_WRITE) ?
					DMA_FROM_DEVICE : DMA_TO_DEVICE));
	sgl_free(fod->data_sg);
	fod->data_sg = NULL;
	fod->data_sg_cnt = 0;
}