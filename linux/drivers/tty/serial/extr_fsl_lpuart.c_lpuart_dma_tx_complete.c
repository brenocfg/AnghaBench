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
struct TYPE_6__ {int tx; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_2__ icount; int /*<<< orphan*/  dev; TYPE_1__* state; } ;
struct lpuart_port {int dma_tx_bytes; int dma_tx_in_progress; TYPE_3__ port; int /*<<< orphan*/  dma_wait; int /*<<< orphan*/  dma_tx_nents; struct scatterlist* tx_sgl; } ;
struct circ_buf {int tail; } ;
struct TYPE_5__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart_dma_tx (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart_stopped_or_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_3__*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lpuart_dma_tx_complete(void *arg)
{
	struct lpuart_port *sport = arg;
	struct scatterlist *sgl = &sport->tx_sgl[0];
	struct circ_buf *xmit = &sport->port.state->xmit;
	unsigned long flags;

	spin_lock_irqsave(&sport->port.lock, flags);

	dma_unmap_sg(sport->port.dev, sgl, sport->dma_tx_nents, DMA_TO_DEVICE);

	xmit->tail = (xmit->tail + sport->dma_tx_bytes) & (UART_XMIT_SIZE - 1);

	sport->port.icount.tx += sport->dma_tx_bytes;
	sport->dma_tx_in_progress = false;
	spin_unlock_irqrestore(&sport->port.lock, flags);

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&sport->port);

	if (waitqueue_active(&sport->dma_wait)) {
		wake_up(&sport->dma_wait);
		return;
	}

	spin_lock_irqsave(&sport->port.lock, flags);

	if (!lpuart_stopped_or_empty(&sport->port))
		lpuart_dma_tx(sport);

	spin_unlock_irqrestore(&sport->port.lock, flags);
}