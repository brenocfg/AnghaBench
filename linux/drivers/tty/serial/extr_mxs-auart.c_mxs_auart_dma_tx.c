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
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct mxs_auart_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_dma_buf; struct dma_chan* tx_dma_chan; struct scatterlist tx_sgl; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {struct mxs_auart_port* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUART_CTRL1_XFER_COUNT (int) ; 
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DMA_TRANS_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_tx_callback ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,struct scatterlist*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mxs_auart_dma_tx(struct mxs_auart_port *s, int size)
{
	struct dma_async_tx_descriptor *desc;
	struct scatterlist *sgl = &s->tx_sgl;
	struct dma_chan *channel = s->tx_dma_chan;
	u32 pio;

	/* [1] : send PIO. Note, the first pio word is CTRL1. */
	pio = AUART_CTRL1_XFER_COUNT(size);
	desc = dmaengine_prep_slave_sg(channel, (struct scatterlist *)&pio,
					1, DMA_TRANS_NONE, 0);
	if (!desc) {
		dev_err(s->dev, "step 1 error\n");
		return -EINVAL;
	}

	/* [2] : set DMA buffer. */
	sg_init_one(sgl, s->tx_dma_buf, size);
	dma_map_sg(s->dev, sgl, 1, DMA_TO_DEVICE);
	desc = dmaengine_prep_slave_sg(channel, sgl,
			1, DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc) {
		dev_err(s->dev, "step 2 error\n");
		return -EINVAL;
	}

	/* [3] : submit the DMA */
	desc->callback = dma_tx_callback;
	desc->callback_param = s;
	dmaengine_submit(desc);
	dma_async_issue_pending(channel);
	return 0;
}