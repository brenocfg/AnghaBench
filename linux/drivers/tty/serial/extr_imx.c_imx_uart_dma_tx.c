#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_4__ {struct device* dev; TYPE_1__* state; } ;
struct imx_port {int dma_is_txing; int dma_tx_nents; int /*<<< orphan*/  tx_bytes; TYPE_2__ port; struct dma_chan* dma_chan_tx; struct scatterlist* tx_sgl; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {struct imx_port* callback_param; int /*<<< orphan*/  callback; } ;
struct device {int dummy; } ;
struct circ_buf {scalar_t__ tail; scalar_t__ head; scalar_t__ buf; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ UART_XMIT_SIZE ; 
 int /*<<< orphan*/  UCR1 ; 
 int /*<<< orphan*/  UCR1_TXDMAEN ; 
 int /*<<< orphan*/  UCR4 ; 
 int /*<<< orphan*/  UCR4_TCEN ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 int dma_map_sg (struct device*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,struct scatterlist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  imx_uart_dma_tx_callback ; 
 int /*<<< orphan*/  imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uart_circ_chars_pending (struct circ_buf*) ; 

__attribute__((used)) static void imx_uart_dma_tx(struct imx_port *sport)
{
	struct circ_buf *xmit = &sport->port.state->xmit;
	struct scatterlist *sgl = sport->tx_sgl;
	struct dma_async_tx_descriptor *desc;
	struct dma_chan	*chan = sport->dma_chan_tx;
	struct device *dev = sport->port.dev;
	u32 ucr1, ucr4;
	int ret;

	if (sport->dma_is_txing)
		return;

	ucr4 = imx_uart_readl(sport, UCR4);
	ucr4 &= ~UCR4_TCEN;
	imx_uart_writel(sport, ucr4, UCR4);

	sport->tx_bytes = uart_circ_chars_pending(xmit);

	if (xmit->tail < xmit->head) {
		sport->dma_tx_nents = 1;
		sg_init_one(sgl, xmit->buf + xmit->tail, sport->tx_bytes);
	} else {
		sport->dma_tx_nents = 2;
		sg_init_table(sgl, 2);
		sg_set_buf(sgl, xmit->buf + xmit->tail,
				UART_XMIT_SIZE - xmit->tail);
		sg_set_buf(sgl + 1, xmit->buf, xmit->head);
	}

	ret = dma_map_sg(dev, sgl, sport->dma_tx_nents, DMA_TO_DEVICE);
	if (ret == 0) {
		dev_err(dev, "DMA mapping error for TX.\n");
		return;
	}
	desc = dmaengine_prep_slave_sg(chan, sgl, sport->dma_tx_nents,
					DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT);
	if (!desc) {
		dma_unmap_sg(dev, sgl, sport->dma_tx_nents,
			     DMA_TO_DEVICE);
		dev_err(dev, "We cannot prepare for the TX slave dma!\n");
		return;
	}
	desc->callback = imx_uart_dma_tx_callback;
	desc->callback_param = sport;

	dev_dbg(dev, "TX: prepare to send %lu bytes by DMA.\n",
			uart_circ_chars_pending(xmit));

	ucr1 = imx_uart_readl(sport, UCR1);
	ucr1 |= UCR1_TXDMAEN;
	imx_uart_writel(sport, ucr1, UCR1);

	/* fire it */
	sport->dma_is_txing = 1;
	dmaengine_submit(desc);
	dma_async_issue_pending(chan);
	return;
}