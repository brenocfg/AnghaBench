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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct imx_port {int dma_tx_nents; int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_per; TYPE_1__ port; int /*<<< orphan*/  timer; int /*<<< orphan*/  gpios; scalar_t__ dma_is_rxing; int /*<<< orphan*/  rx_sgl; int /*<<< orphan*/  dma_chan_rx; scalar_t__ dma_is_txing; int /*<<< orphan*/ * tx_sgl; int /*<<< orphan*/  dma_chan_tx; scalar_t__ dma_is_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  UCR1 ; 
 int UCR1_ATDMAEN ; 
 int UCR1_RRDYEN ; 
 int UCR1_RTSDEN ; 
 int UCR1_RXDMAEN ; 
 int UCR1_TRDYEN ; 
 int UCR1_UARTEN ; 
 int /*<<< orphan*/  UCR2 ; 
 int UCR2_ATEN ; 
 int UCR2_TXEN ; 
 int /*<<< orphan*/  UCR4 ; 
 int UCR4_OREN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_disable_dma (struct imx_port*) ; 
 int /*<<< orphan*/  imx_uart_dma_exit (struct imx_port*) ; 
 int imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_stop_rx (struct uart_port*) ; 
 int /*<<< orphan*/  imx_uart_stop_tx (struct uart_port*) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mctrl_gpio_disable_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void imx_uart_shutdown(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned long flags;
	u32 ucr1, ucr2, ucr4;

	if (sport->dma_is_enabled) {
		dmaengine_terminate_sync(sport->dma_chan_tx);
		if (sport->dma_is_txing) {
			dma_unmap_sg(sport->port.dev, &sport->tx_sgl[0],
				     sport->dma_tx_nents, DMA_TO_DEVICE);
			sport->dma_is_txing = 0;
		}
		dmaengine_terminate_sync(sport->dma_chan_rx);
		if (sport->dma_is_rxing) {
			dma_unmap_sg(sport->port.dev, &sport->rx_sgl,
				     1, DMA_FROM_DEVICE);
			sport->dma_is_rxing = 0;
		}

		spin_lock_irqsave(&sport->port.lock, flags);
		imx_uart_stop_tx(port);
		imx_uart_stop_rx(port);
		imx_uart_disable_dma(sport);
		spin_unlock_irqrestore(&sport->port.lock, flags);
		imx_uart_dma_exit(sport);
	}

	mctrl_gpio_disable_ms(sport->gpios);

	spin_lock_irqsave(&sport->port.lock, flags);
	ucr2 = imx_uart_readl(sport, UCR2);
	ucr2 &= ~(UCR2_TXEN | UCR2_ATEN);
	imx_uart_writel(sport, ucr2, UCR2);

	ucr4 = imx_uart_readl(sport, UCR4);
	ucr4 &= ~UCR4_OREN;
	imx_uart_writel(sport, ucr4, UCR4);
	spin_unlock_irqrestore(&sport->port.lock, flags);

	/*
	 * Stop our timer.
	 */
	del_timer_sync(&sport->timer);

	/*
	 * Disable all interrupts, port and break condition.
	 */

	spin_lock_irqsave(&sport->port.lock, flags);
	ucr1 = imx_uart_readl(sport, UCR1);
	ucr1 &= ~(UCR1_TRDYEN | UCR1_RRDYEN | UCR1_RTSDEN | UCR1_UARTEN | UCR1_RXDMAEN | UCR1_ATDMAEN);

	imx_uart_writel(sport, ucr1, UCR1);
	spin_unlock_irqrestore(&sport->port.lock, flags);

	clk_disable_unprepare(sport->clk_per);
	clk_disable_unprepare(sport->clk_ipg);
}