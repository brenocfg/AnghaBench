#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nand_chip {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct mtd_info {TYPE_1__ dev; } ;
struct lpc32xx_nand_host {int /*<<< orphan*/  sgl; TYPE_3__* dma_chan; int /*<<< orphan*/  comp_dma; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/ * callback_param; int /*<<< orphan*/  callback; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
struct TYPE_7__ {TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int DMA_CTRL_ACK ; 
 int DMA_PREP_INTERRUPT ; 
 int ENXIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (TYPE_3__*) ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (TYPE_3__*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpc32xx_dma_complete_func ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc32xx_xmit_dma(struct mtd_info *mtd, void *mem, int len,
			    enum dma_transfer_direction dir)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);
	struct dma_async_tx_descriptor *desc;
	int flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	int res;

	sg_init_one(&host->sgl, mem, len);

	res = dma_map_sg(host->dma_chan->device->dev, &host->sgl, 1,
			 DMA_BIDIRECTIONAL);
	if (res != 1) {
		dev_err(mtd->dev.parent, "Failed to map sg list\n");
		return -ENXIO;
	}
	desc = dmaengine_prep_slave_sg(host->dma_chan, &host->sgl, 1, dir,
				       flags);
	if (!desc) {
		dev_err(mtd->dev.parent, "Failed to prepare slave sg\n");
		goto out1;
	}

	init_completion(&host->comp_dma);
	desc->callback = lpc32xx_dma_complete_func;
	desc->callback_param = &host->comp_dma;

	dmaengine_submit(desc);
	dma_async_issue_pending(host->dma_chan);

	wait_for_completion_timeout(&host->comp_dma, msecs_to_jiffies(1000));

	dma_unmap_sg(host->dma_chan->device->dev, &host->sgl, 1,
		     DMA_BIDIRECTIONAL);
	return 0;
out1:
	dma_unmap_sg(host->dma_chan->device->dev, &host->sgl, 1,
		     DMA_BIDIRECTIONAL);
	return -ENXIO;
}