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
struct TYPE_4__ {unsigned int rx; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_2__ icount; int /*<<< orphan*/  dev; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct atmel_uart_port {int pdc_rx_idx; struct atmel_dma_buffer* pdc_rx; } ;
struct atmel_dma_buffer {unsigned int dma_size; unsigned int dma_addr; unsigned int ofs; scalar_t__ buf; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PDC_RNCR ; 
 int /*<<< orphan*/  ATMEL_PDC_RNPR ; 
 int /*<<< orphan*/  ATMEL_PDC_RPR ; 
 int /*<<< orphan*/  ATMEL_US_CR ; 
 int ATMEL_US_ENDRX ; 
 int /*<<< orphan*/  ATMEL_US_IER ; 
 int ATMEL_US_STTTO ; 
 int ATMEL_US_TIMEOUT ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_port*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void atmel_rx_from_pdc(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct tty_port *tport = &port->state->port;
	struct atmel_dma_buffer *pdc;
	int rx_idx = atmel_port->pdc_rx_idx;
	unsigned int head;
	unsigned int tail;
	unsigned int count;

	do {
		/* Reset the UART timeout early so that we don't miss one */
		atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_STTTO);

		pdc = &atmel_port->pdc_rx[rx_idx];
		head = atmel_uart_readl(port, ATMEL_PDC_RPR) - pdc->dma_addr;
		tail = pdc->ofs;

		/* If the PDC has switched buffers, RPR won't contain
		 * any address within the current buffer. Since head
		 * is unsigned, we just need a one-way comparison to
		 * find out.
		 *
		 * In this case, we just need to consume the entire
		 * buffer and resubmit it for DMA. This will clear the
		 * ENDRX bit as well, so that we can safely re-enable
		 * all interrupts below.
		 */
		head = min(head, pdc->dma_size);

		if (likely(head != tail)) {
			dma_sync_single_for_cpu(port->dev, pdc->dma_addr,
					pdc->dma_size, DMA_FROM_DEVICE);

			/*
			 * head will only wrap around when we recycle
			 * the DMA buffer, and when that happens, we
			 * explicitly set tail to 0. So head will
			 * always be greater than tail.
			 */
			count = head - tail;

			tty_insert_flip_string(tport, pdc->buf + pdc->ofs,
						count);

			dma_sync_single_for_device(port->dev, pdc->dma_addr,
					pdc->dma_size, DMA_FROM_DEVICE);

			port->icount.rx += count;
			pdc->ofs = head;
		}

		/*
		 * If the current buffer is full, we need to check if
		 * the next one contains any additional data.
		 */
		if (head >= pdc->dma_size) {
			pdc->ofs = 0;
			atmel_uart_writel(port, ATMEL_PDC_RNPR, pdc->dma_addr);
			atmel_uart_writel(port, ATMEL_PDC_RNCR, pdc->dma_size);

			rx_idx = !rx_idx;
			atmel_port->pdc_rx_idx = rx_idx;
		}
	} while (head >= pdc->dma_size);

	/*
	 * Drop the lock here since it might end up calling
	 * uart_start(), which takes the lock.
	 */
	spin_unlock(&port->lock);
	tty_flip_buffer_push(tport);
	spin_lock(&port->lock);

	atmel_uart_writel(port, ATMEL_US_IER,
			  ATMEL_US_ENDRX | ATMEL_US_TIMEOUT);
}