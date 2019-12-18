#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_port {int dummy; } ;
struct imx_port {scalar_t__ dma_is_txing; } ;

/* Variables and functions */
 unsigned int TIOCSER_TEMT ; 
 int /*<<< orphan*/  USR2 ; 
 int USR2_TXDC ; 
 int imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int imx_uart_tx_empty(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned int ret;

	ret = (imx_uart_readl(sport, USR2) & USR2_TXDC) ?  TIOCSER_TEMT : 0;

	/* If the TX DMA is working, return 0. */
	if (sport->dma_is_txing)
		ret = 0;

	return ret;
}