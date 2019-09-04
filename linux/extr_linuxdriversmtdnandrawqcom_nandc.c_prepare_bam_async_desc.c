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
struct scatterlist {int dummy; } ;
struct qcom_nand_controller {int /*<<< orphan*/  desc_list; struct dma_chan* cmd_chan; int /*<<< orphan*/  dev; struct dma_chan* tx_chan; struct bam_transaction* bam_txn; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct desc_info {unsigned int sgl_cnt; int /*<<< orphan*/  node; struct dma_async_tx_descriptor* dma_desc; void* dir; struct scatterlist* bam_sgl; } ;
struct bam_transaction {size_t cmd_sgl_start; unsigned int cmd_sgl_pos; size_t tx_sgl_start; unsigned int tx_sgl_pos; size_t rx_sgl_start; unsigned int rx_sgl_pos; struct dma_async_tx_descriptor* last_data_desc; struct dma_async_tx_descriptor* last_cmd_desc; struct scatterlist* data_sgl; struct scatterlist* cmd_sgl; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 void* DMA_FROM_DEVICE ; 
 int DMA_MEM_TO_DEV ; 
 void* DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,unsigned int,void*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,unsigned int,void*) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,struct scatterlist*,unsigned int,int,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct desc_info*) ; 
 struct desc_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 

__attribute__((used)) static int prepare_bam_async_desc(struct qcom_nand_controller *nandc,
				  struct dma_chan *chan,
				  unsigned long flags)
{
	struct desc_info *desc;
	struct scatterlist *sgl;
	unsigned int sgl_cnt;
	int ret;
	struct bam_transaction *bam_txn = nandc->bam_txn;
	enum dma_transfer_direction dir_eng;
	struct dma_async_tx_descriptor *dma_desc;

	desc = kzalloc(sizeof(*desc), GFP_KERNEL);
	if (!desc)
		return -ENOMEM;

	if (chan == nandc->cmd_chan) {
		sgl = &bam_txn->cmd_sgl[bam_txn->cmd_sgl_start];
		sgl_cnt = bam_txn->cmd_sgl_pos - bam_txn->cmd_sgl_start;
		bam_txn->cmd_sgl_start = bam_txn->cmd_sgl_pos;
		dir_eng = DMA_MEM_TO_DEV;
		desc->dir = DMA_TO_DEVICE;
	} else if (chan == nandc->tx_chan) {
		sgl = &bam_txn->data_sgl[bam_txn->tx_sgl_start];
		sgl_cnt = bam_txn->tx_sgl_pos - bam_txn->tx_sgl_start;
		bam_txn->tx_sgl_start = bam_txn->tx_sgl_pos;
		dir_eng = DMA_MEM_TO_DEV;
		desc->dir = DMA_TO_DEVICE;
	} else {
		sgl = &bam_txn->data_sgl[bam_txn->rx_sgl_start];
		sgl_cnt = bam_txn->rx_sgl_pos - bam_txn->rx_sgl_start;
		bam_txn->rx_sgl_start = bam_txn->rx_sgl_pos;
		dir_eng = DMA_DEV_TO_MEM;
		desc->dir = DMA_FROM_DEVICE;
	}

	sg_mark_end(sgl + sgl_cnt - 1);
	ret = dma_map_sg(nandc->dev, sgl, sgl_cnt, desc->dir);
	if (ret == 0) {
		dev_err(nandc->dev, "failure in mapping desc\n");
		kfree(desc);
		return -ENOMEM;
	}

	desc->sgl_cnt = sgl_cnt;
	desc->bam_sgl = sgl;

	dma_desc = dmaengine_prep_slave_sg(chan, sgl, sgl_cnt, dir_eng,
					   flags);

	if (!dma_desc) {
		dev_err(nandc->dev, "failure in prep desc\n");
		dma_unmap_sg(nandc->dev, sgl, sgl_cnt, desc->dir);
		kfree(desc);
		return -EINVAL;
	}

	desc->dma_desc = dma_desc;

	/* update last data/command descriptor */
	if (chan == nandc->cmd_chan)
		bam_txn->last_cmd_desc = dma_desc;
	else
		bam_txn->last_data_desc = dma_desc;

	list_add_tail(&desc->node, &nandc->desc_list);

	return 0;
}