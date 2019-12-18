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
struct TYPE_4__ {int tx; } ;
struct uart_port {int /*<<< orphan*/  dev; TYPE_2__ icount; TYPE_1__* state; } ;
struct circ_buf {int tail; int /*<<< orphan*/  head; } ;
struct atmel_dma_buffer {int ofs; int dma_addr; int /*<<< orphan*/  dma_size; } ;
struct atmel_uart_port {int tx_done_mask; struct atmel_dma_buffer pdc_tx; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PDC_PTCR ; 
 int /*<<< orphan*/  ATMEL_PDC_TCR ; 
 int /*<<< orphan*/  ATMEL_PDC_TPR ; 
 int ATMEL_PDC_TXTDIS ; 
 int ATMEL_PDC_TXTEN ; 
 int /*<<< orphan*/  ATMEL_US_IER ; 
 int CIRC_CNT_TO_END (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  atmel_start_rx (struct uart_port*) ; 
 scalar_t__ atmel_uart_is_half_duplex (struct uart_port*) ; 
 scalar_t__ atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

__attribute__((used)) static void atmel_tx_pdc(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct circ_buf *xmit = &port->state->xmit;
	struct atmel_dma_buffer *pdc = &atmel_port->pdc_tx;
	int count;

	/* nothing left to transmit? */
	if (atmel_uart_readl(port, ATMEL_PDC_TCR))
		return;

	xmit->tail += pdc->ofs;
	xmit->tail &= UART_XMIT_SIZE - 1;

	port->icount.tx += pdc->ofs;
	pdc->ofs = 0;

	/* more to transmit - setup next transfer */

	/* disable PDC transmit */
	atmel_uart_writel(port, ATMEL_PDC_PTCR, ATMEL_PDC_TXTDIS);

	if (!uart_circ_empty(xmit) && !uart_tx_stopped(port)) {
		dma_sync_single_for_device(port->dev,
					   pdc->dma_addr,
					   pdc->dma_size,
					   DMA_TO_DEVICE);

		count = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);
		pdc->ofs = count;

		atmel_uart_writel(port, ATMEL_PDC_TPR,
				  pdc->dma_addr + xmit->tail);
		atmel_uart_writel(port, ATMEL_PDC_TCR, count);
		/* re-enable PDC transmit */
		atmel_uart_writel(port, ATMEL_PDC_PTCR, ATMEL_PDC_TXTEN);
		/* Enable interrupts */
		atmel_uart_writel(port, ATMEL_US_IER,
				  atmel_port->tx_done_mask);
	} else {
		if (atmel_uart_is_half_duplex(port)) {
			/* DMA done, stop TX, start RX for RS485 */
			atmel_start_rx(port);
		}
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);
}