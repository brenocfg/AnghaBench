#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int flags; } ;
struct uart_port {TYPE_1__ rs485; } ;
struct imx_port {scalar_t__ dma_is_txing; } ;

/* Variables and functions */
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_AFTER_SEND ; 
 int /*<<< orphan*/  UCR1 ; 
 int UCR1_TRDYEN ; 
 int /*<<< orphan*/  UCR2 ; 
 int /*<<< orphan*/  UCR4 ; 
 int UCR4_TCEN ; 
 int /*<<< orphan*/  USR2 ; 
 int USR2_TXDC ; 
 int imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_rts_active (struct imx_port*,int*) ; 
 int /*<<< orphan*/  imx_uart_rts_inactive (struct imx_port*,int*) ; 
 int /*<<< orphan*/  imx_uart_start_rx (struct uart_port*) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_uart_stop_tx(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	u32 ucr1;

	/*
	 * We are maybe in the SMP context, so if the DMA TX thread is running
	 * on other cpu, we have to wait for it to finish.
	 */
	if (sport->dma_is_txing)
		return;

	ucr1 = imx_uart_readl(sport, UCR1);
	imx_uart_writel(sport, ucr1 & ~UCR1_TRDYEN, UCR1);

	/* in rs485 mode disable transmitter if shifter is empty */
	if (port->rs485.flags & SER_RS485_ENABLED &&
	    imx_uart_readl(sport, USR2) & USR2_TXDC) {
		u32 ucr2 = imx_uart_readl(sport, UCR2), ucr4;
		if (port->rs485.flags & SER_RS485_RTS_AFTER_SEND)
			imx_uart_rts_active(sport, &ucr2);
		else
			imx_uart_rts_inactive(sport, &ucr2);
		imx_uart_writel(sport, ucr2, UCR2);

		imx_uart_start_rx(port);

		ucr4 = imx_uart_readl(sport, UCR4);
		ucr4 &= ~UCR4_TCEN;
		imx_uart_writel(sport, ucr4, UCR4);
	}
}