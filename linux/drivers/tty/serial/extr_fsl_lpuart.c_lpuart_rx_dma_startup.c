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
struct lpuart_port {int dma_rx_timeout; int lpuart_dma_rx_use; scalar_t__ dma_rx_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RX_TIMEOUT ; 
 int /*<<< orphan*/  lpuart_start_rx_dma (struct lpuart_port*) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_dma_timer_init (struct lpuart_port*) ; 

__attribute__((used)) static void lpuart_rx_dma_startup(struct lpuart_port *sport)
{
	if (sport->dma_rx_chan && !lpuart_start_rx_dma(sport)) {
		/* set Rx DMA timeout */
		sport->dma_rx_timeout = msecs_to_jiffies(DMA_RX_TIMEOUT);
		if (!sport->dma_rx_timeout)
			sport->dma_rx_timeout = 1;

		sport->lpuart_dma_rx_use = true;
		rx_dma_timer_init(sport);
	} else {
		sport->lpuart_dma_rx_use = false;
	}
}