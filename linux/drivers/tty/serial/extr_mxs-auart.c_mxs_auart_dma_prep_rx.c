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
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct mxs_auart_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_dma_buf; struct dma_chan* rx_dma_chan; struct scatterlist rx_sgl; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {struct mxs_auart_port* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int AUART_CTRL0_RXTIMEOUT (int) ; 
 int AUART_CTRL0_RXTO_ENABLE ; 
 int AUART_CTRL0_XFER_COUNT (int /*<<< orphan*/ ) ; 
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TRANS_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  UART_XMIT_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_rx_callback ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,struct scatterlist*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxs_auart_dma_prep_rx(struct mxs_auart_port *s)
{
	struct dma_async_tx_descriptor *desc;
	struct scatterlist *sgl = &s->rx_sgl;
	struct dma_chan *channel = s->rx_dma_chan;
	u32 pio[1];

	/* [1] : send PIO */
	pio[0] = AUART_CTRL0_RXTO_ENABLE
		| AUART_CTRL0_RXTIMEOUT(0x80)
		| AUART_CTRL0_XFER_COUNT(UART_XMIT_SIZE);
	desc = dmaengine_prep_slave_sg(channel, (struct scatterlist *)pio,
					1, DMA_TRANS_NONE, 0);
	if (!desc) {
		dev_err(s->dev, "step 1 error\n");
		return -EINVAL;
	}

	/* [2] : send DMA request */
	sg_init_one(sgl, s->rx_dma_buf, UART_XMIT_SIZE);
	dma_map_sg(s->dev, sgl, 1, DMA_FROM_DEVICE);
	desc = dmaengine_prep_slave_sg(channel, sgl, 1, DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc) {
		dev_err(s->dev, "step 2 error\n");
		return -1;
	}

	/* [3] : submit the DMA, but do not issue it. */
	desc->callback = dma_rx_callback;
	desc->callback_param = s;
	dmaengine_submit(desc);
	dma_async_issue_pending(channel);
	return 0;
}