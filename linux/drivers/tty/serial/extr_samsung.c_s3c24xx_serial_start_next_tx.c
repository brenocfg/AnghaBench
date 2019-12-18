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
struct uart_port {TYPE_2__* state; } ;
struct s3c24xx_uart_port {unsigned long min_dma_size; TYPE_1__* dma; struct uart_port port; } ;
struct circ_buf {int tail; int /*<<< orphan*/  head; } ;
struct TYPE_4__ {struct circ_buf xmit; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_chan; } ;

/* Variables and functions */
 unsigned long CIRC_CNT_TO_END (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_XMIT_SIZE ; 
 int dma_get_cache_alignment () ; 
 int /*<<< orphan*/  s3c24xx_serial_start_tx_dma (struct s3c24xx_uart_port*,unsigned long) ; 
 int /*<<< orphan*/  s3c24xx_serial_start_tx_pio (struct s3c24xx_uart_port*) ; 
 int /*<<< orphan*/  s3c24xx_serial_stop_tx (struct uart_port*) ; 

__attribute__((used)) static void s3c24xx_serial_start_next_tx(struct s3c24xx_uart_port *ourport)
{
	struct uart_port *port = &ourport->port;
	struct circ_buf *xmit = &port->state->xmit;
	unsigned long count;

	/* Get data size up to the end of buffer */
	count = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);

	if (!count) {
		s3c24xx_serial_stop_tx(port);
		return;
	}

	if (!ourport->dma || !ourport->dma->tx_chan ||
	    count < ourport->min_dma_size ||
	    xmit->tail & (dma_get_cache_alignment() - 1))
		s3c24xx_serial_start_tx_pio(ourport);
	else
		s3c24xx_serial_start_tx_dma(ourport, count);
}