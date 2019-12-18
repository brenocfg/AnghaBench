#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  tx; } ;
struct TYPE_8__ {int x_char; TYPE_2__ icount; TYPE_1__* state; } ;
struct imx_port {TYPE_3__ port; scalar_t__ dma_is_txing; scalar_t__ dma_is_enabled; } ;
struct circ_buf {int* buf; size_t tail; } ;
struct TYPE_6__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int UART_XMIT_SIZE ; 
 int /*<<< orphan*/  UCR1 ; 
 int UCR1_TRDYEN ; 
 int UCR1_TXDMAEN ; 
 int /*<<< orphan*/  URTX0 ; 
 int UTS_TXFULL ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  imx_uart_dma_tx (struct imx_port*) ; 
 int imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_stop_tx (TYPE_3__*) ; 
 int /*<<< orphan*/  imx_uart_uts_reg (struct imx_port*) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (TYPE_3__*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_3__*) ; 

__attribute__((used)) static inline void imx_uart_transmit_buffer(struct imx_port *sport)
{
	struct circ_buf *xmit = &sport->port.state->xmit;

	if (sport->port.x_char) {
		/* Send next char */
		imx_uart_writel(sport, sport->port.x_char, URTX0);
		sport->port.icount.tx++;
		sport->port.x_char = 0;
		return;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(&sport->port)) {
		imx_uart_stop_tx(&sport->port);
		return;
	}

	if (sport->dma_is_enabled) {
		u32 ucr1;
		/*
		 * We've just sent a X-char Ensure the TX DMA is enabled
		 * and the TX IRQ is disabled.
		 **/
		ucr1 = imx_uart_readl(sport, UCR1);
		ucr1 &= ~UCR1_TRDYEN;
		if (sport->dma_is_txing) {
			ucr1 |= UCR1_TXDMAEN;
			imx_uart_writel(sport, ucr1, UCR1);
		} else {
			imx_uart_writel(sport, ucr1, UCR1);
			imx_uart_dma_tx(sport);
		}

		return;
	}

	while (!uart_circ_empty(xmit) &&
	       !(imx_uart_readl(sport, imx_uart_uts_reg(sport)) & UTS_TXFULL)) {
		/* send xmit->buf[xmit->tail]
		 * out the port here */
		imx_uart_writel(sport, xmit->buf[xmit->tail], URTX0);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&sport->port);

	if (uart_circ_empty(xmit))
		imx_uart_stop_tx(&sport->port);
}