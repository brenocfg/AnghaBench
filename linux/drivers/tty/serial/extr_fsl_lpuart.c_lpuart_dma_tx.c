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
struct scatterlist {int dummy; } ;
struct TYPE_6__ {struct device* dev; TYPE_1__* state; } ;
struct lpuart_port {int dma_tx_in_progress; int dma_tx_nents; int /*<<< orphan*/  dma_tx_chan; TYPE_3__* dma_tx_desc; int /*<<< orphan*/  dma_tx_cookie; int /*<<< orphan*/  dma_tx_bytes; TYPE_2__ port; struct scatterlist* tx_sgl; } ;
struct device {int dummy; } ;
struct circ_buf {scalar_t__ tail; scalar_t__ head; scalar_t__ buf; } ;
struct TYPE_7__ {struct lpuart_port* callback_param; int /*<<< orphan*/  callback; } ;
struct TYPE_5__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ UART_XMIT_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int dma_map_sg (struct device*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (TYPE_3__*) ; 
 int /*<<< orphan*/  lpuart_dma_tx_complete ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uart_circ_chars_pending (struct circ_buf*) ; 

__attribute__((used)) static void lpuart_dma_tx(struct lpuart_port *sport)
{
	struct circ_buf *xmit = &sport->port.state->xmit;
	struct scatterlist *sgl = sport->tx_sgl;
	struct device *dev = sport->port.dev;
	int ret;

	if (sport->dma_tx_in_progress)
		return;

	sport->dma_tx_bytes = uart_circ_chars_pending(xmit);

	if (xmit->tail < xmit->head || xmit->head == 0) {
		sport->dma_tx_nents = 1;
		sg_init_one(sgl, xmit->buf + xmit->tail, sport->dma_tx_bytes);
	} else {
		sport->dma_tx_nents = 2;
		sg_init_table(sgl, 2);
		sg_set_buf(sgl, xmit->buf + xmit->tail,
				UART_XMIT_SIZE - xmit->tail);
		sg_set_buf(sgl + 1, xmit->buf, xmit->head);
	}

	ret = dma_map_sg(dev, sgl, sport->dma_tx_nents, DMA_TO_DEVICE);
	if (!ret) {
		dev_err(dev, "DMA mapping error for TX.\n");
		return;
	}

	sport->dma_tx_desc = dmaengine_prep_slave_sg(sport->dma_tx_chan, sgl,
					sport->dma_tx_nents,
					DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT);
	if (!sport->dma_tx_desc) {
		dma_unmap_sg(dev, sgl, sport->dma_tx_nents, DMA_TO_DEVICE);
		dev_err(dev, "Cannot prepare TX slave DMA!\n");
		return;
	}

	sport->dma_tx_desc->callback = lpuart_dma_tx_complete;
	sport->dma_tx_desc->callback_param = sport;
	sport->dma_tx_in_progress = true;
	sport->dma_tx_cookie = dmaengine_submit(sport->dma_tx_desc);
	dma_async_issue_pending(sport->dma_tx_chan);
}