#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* state; } ;
struct uart_8250_port {TYPE_3__ port; struct uart_8250_dma* dma; } ;
struct uart_8250_dma {int tx_running; int tx_err; TYPE_4__* txchan; scalar_t__ tx_addr; int /*<<< orphan*/  tx_cookie; int /*<<< orphan*/  tx_size; } ;
struct dma_async_tx_descriptor {struct uart_8250_port* callback_param; int /*<<< orphan*/  callback; } ;
struct circ_buf {scalar_t__ tail; int /*<<< orphan*/  head; } ;
struct TYPE_9__ {TYPE_2__* device; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_CNT_TO_END (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EBUSY ; 
 int /*<<< orphan*/  UART_XMIT_SIZE ; 
 int /*<<< orphan*/  __dma_tx_complete ; 
 int /*<<< orphan*/  dma_async_issue_pending (TYPE_4__*) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_single (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  serial8250_clear_THRI (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_put_tx (struct uart_8250_port*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (TYPE_3__*) ; 

int serial8250_tx_dma(struct uart_8250_port *p)
{
	struct uart_8250_dma		*dma = p->dma;
	struct circ_buf			*xmit = &p->port.state->xmit;
	struct dma_async_tx_descriptor	*desc;
	int ret;

	if (dma->tx_running)
		return 0;

	if (uart_tx_stopped(&p->port) || uart_circ_empty(xmit)) {
		/* We have been called from __dma_tx_complete() */
		serial8250_rpm_put_tx(p);
		return 0;
	}

	dma->tx_size = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);

	desc = dmaengine_prep_slave_single(dma->txchan,
					   dma->tx_addr + xmit->tail,
					   dma->tx_size, DMA_MEM_TO_DEV,
					   DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc) {
		ret = -EBUSY;
		goto err;
	}

	dma->tx_running = 1;
	desc->callback = __dma_tx_complete;
	desc->callback_param = p;

	dma->tx_cookie = dmaengine_submit(desc);

	dma_sync_single_for_device(dma->txchan->device->dev, dma->tx_addr,
				   UART_XMIT_SIZE, DMA_TO_DEVICE);

	dma_async_issue_pending(dma->txchan);
	if (dma->tx_err) {
		dma->tx_err = 0;
		serial8250_clear_THRI(p);
	}
	return 0;
err:
	dma->tx_err = 1;
	return ret;
}