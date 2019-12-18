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
struct uart_port {int dummy; } ;
struct scatterlist {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct imx_port {scalar_t__ dma_is_txing; int /*<<< orphan*/  dma_tx_nents; TYPE_1__ port; int /*<<< orphan*/  dma_chan_tx; scalar_t__ tx_bytes; struct scatterlist* tx_sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IMX21_UTS ; 
 int /*<<< orphan*/  UBIR ; 
 int /*<<< orphan*/  UBMR ; 
 int /*<<< orphan*/  UCR1 ; 
 int UCR1_TXDMAEN ; 
 int /*<<< orphan*/  UCR2 ; 
 int UCR2_SRST ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void imx_uart_flush_buffer(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	struct scatterlist *sgl = &sport->tx_sgl[0];
	u32 ucr2;
	int i = 100, ubir, ubmr, uts;

	if (!sport->dma_chan_tx)
		return;

	sport->tx_bytes = 0;
	dmaengine_terminate_all(sport->dma_chan_tx);
	if (sport->dma_is_txing) {
		u32 ucr1;

		dma_unmap_sg(sport->port.dev, sgl, sport->dma_tx_nents,
			     DMA_TO_DEVICE);
		ucr1 = imx_uart_readl(sport, UCR1);
		ucr1 &= ~UCR1_TXDMAEN;
		imx_uart_writel(sport, ucr1, UCR1);
		sport->dma_is_txing = 0;
	}

	/*
	 * According to the Reference Manual description of the UART SRST bit:
	 *
	 * "Reset the transmit and receive state machines,
	 * all FIFOs and register USR1, USR2, UBIR, UBMR, UBRC, URXD, UTXD
	 * and UTS[6-3]".
	 *
	 * We don't need to restore the old values from USR1, USR2, URXD and
	 * UTXD. UBRC is read only, so only save/restore the other three
	 * registers.
	 */
	ubir = imx_uart_readl(sport, UBIR);
	ubmr = imx_uart_readl(sport, UBMR);
	uts = imx_uart_readl(sport, IMX21_UTS);

	ucr2 = imx_uart_readl(sport, UCR2);
	ucr2 &= ~UCR2_SRST;
	imx_uart_writel(sport, ucr2, UCR2);

	while (!(imx_uart_readl(sport, UCR2) & UCR2_SRST) && (--i > 0))
		udelay(1);

	/* Restore the registers */
	imx_uart_writel(sport, ubir, UBIR);
	imx_uart_writel(sport, ubmr, UBMR);
	imx_uart_writel(sport, uts, IMX21_UTS);
}