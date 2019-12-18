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
struct tty_port {int dummy; } ;
struct TYPE_7__ {int rx; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_2__ icount; scalar_t__ membase; TYPE_1__* state; } ;
struct TYPE_9__ {scalar_t__ length; } ;
struct circ_buf {scalar_t__ head; scalar_t__ tail; int buf; } ;
struct lpuart_port {scalar_t__ dma_rx_timeout; int /*<<< orphan*/  lpuart_timer; TYPE_3__ port; TYPE_4__ rx_sgl; int /*<<< orphan*/  dma_rx_cookie; int /*<<< orphan*/  dma_rx_chan; int /*<<< orphan*/  dma_rx_desc; struct circ_buf rx_ring; } ;
struct dma_tx_state {scalar_t__ residue; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
struct TYPE_6__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_ERROR ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ UARTCFIFO ; 
 unsigned char UARTCFIFO_RXFLUSH ; 
 scalar_t__ UARTCR2 ; 
 unsigned char UARTCR2_RE ; 
 int /*<<< orphan*/  UARTDATA ; 
 scalar_t__ UARTDR ; 
 scalar_t__ UARTSFIFO ; 
 int UARTSFIFO_RXUF ; 
 scalar_t__ UARTSR1 ; 
 unsigned char UARTSR1_FE ; 
 unsigned char UARTSR1_PE ; 
 int /*<<< orphan*/  UARTSTAT ; 
 unsigned long UARTSTAT_FE ; 
 unsigned long UARTSTAT_PE ; 
 int /*<<< orphan*/  async_tx_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_sync_sg_for_cpu (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_sg_for_device (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 scalar_t__ jiffies ; 
 unsigned long lpuart32_read (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpuart_is_32 (struct lpuart_port*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_port*,int,int) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void lpuart_copy_rx_to_tty(struct lpuart_port *sport)
{
	struct tty_port *port = &sport->port.state->port;
	struct dma_tx_state state;
	enum dma_status dmastat;
	struct circ_buf *ring = &sport->rx_ring;
	unsigned long flags;
	int count = 0;

	if (lpuart_is_32(sport)) {
		unsigned long sr = lpuart32_read(&sport->port, UARTSTAT);

		if (sr & (UARTSTAT_PE | UARTSTAT_FE)) {
			/* Read DR to clear the error flags */
			lpuart32_read(&sport->port, UARTDATA);

			if (sr & UARTSTAT_PE)
				sport->port.icount.parity++;
			else if (sr & UARTSTAT_FE)
				sport->port.icount.frame++;
		}
	} else {
		unsigned char sr = readb(sport->port.membase + UARTSR1);

		if (sr & (UARTSR1_PE | UARTSR1_FE)) {
			unsigned char cr2;

			/* Disable receiver during this operation... */
			cr2 = readb(sport->port.membase + UARTCR2);
			cr2 &= ~UARTCR2_RE;
			writeb(cr2, sport->port.membase + UARTCR2);

			/* Read DR to clear the error flags */
			readb(sport->port.membase + UARTDR);

			if (sr & UARTSR1_PE)
				sport->port.icount.parity++;
			else if (sr & UARTSR1_FE)
				sport->port.icount.frame++;
			/*
			 * At this point parity/framing error is
			 * cleared However, since the DMA already read
			 * the data register and we had to read it
			 * again after reading the status register to
			 * properly clear the flags, the FIFO actually
			 * underflowed... This requires a clearing of
			 * the FIFO...
			 */
			if (readb(sport->port.membase + UARTSFIFO) &
			    UARTSFIFO_RXUF) {
				writeb(UARTSFIFO_RXUF,
				       sport->port.membase + UARTSFIFO);
				writeb(UARTCFIFO_RXFLUSH,
				       sport->port.membase + UARTCFIFO);
			}

			cr2 |= UARTCR2_RE;
			writeb(cr2, sport->port.membase + UARTCR2);
		}
	}

	async_tx_ack(sport->dma_rx_desc);

	spin_lock_irqsave(&sport->port.lock, flags);

	dmastat = dmaengine_tx_status(sport->dma_rx_chan,
				sport->dma_rx_cookie,
				&state);

	if (dmastat == DMA_ERROR) {
		dev_err(sport->port.dev, "Rx DMA transfer failed!\n");
		spin_unlock_irqrestore(&sport->port.lock, flags);
		return;
	}

	/* CPU claims ownership of RX DMA buffer */
	dma_sync_sg_for_cpu(sport->port.dev, &sport->rx_sgl, 1, DMA_FROM_DEVICE);

	/*
	 * ring->head points to the end of data already written by the DMA.
	 * ring->tail points to the beginning of data to be read by the
	 * framework.
	 * The current transfer size should not be larger than the dma buffer
	 * length.
	 */
	ring->head = sport->rx_sgl.length - state.residue;
	BUG_ON(ring->head > sport->rx_sgl.length);
	/*
	 * At this point ring->head may point to the first byte right after the
	 * last byte of the dma buffer:
	 * 0 <= ring->head <= sport->rx_sgl.length
	 *
	 * However ring->tail must always points inside the dma buffer:
	 * 0 <= ring->tail <= sport->rx_sgl.length - 1
	 *
	 * Since we use a ring buffer, we have to handle the case
	 * where head is lower than tail. In such a case, we first read from
	 * tail to the end of the buffer then reset tail.
	 */
	if (ring->head < ring->tail) {
		count = sport->rx_sgl.length - ring->tail;

		tty_insert_flip_string(port, ring->buf + ring->tail, count);
		ring->tail = 0;
		sport->port.icount.rx += count;
	}

	/* Finally we read data from tail to head */
	if (ring->tail < ring->head) {
		count = ring->head - ring->tail;
		tty_insert_flip_string(port, ring->buf + ring->tail, count);
		/* Wrap ring->head if needed */
		if (ring->head >= sport->rx_sgl.length)
			ring->head = 0;
		ring->tail = ring->head;
		sport->port.icount.rx += count;
	}

	dma_sync_sg_for_device(sport->port.dev, &sport->rx_sgl, 1,
			       DMA_FROM_DEVICE);

	spin_unlock_irqrestore(&sport->port.lock, flags);

	tty_flip_buffer_push(port);
	mod_timer(&sport->lpuart_timer, jiffies + sport->dma_rx_timeout);
}