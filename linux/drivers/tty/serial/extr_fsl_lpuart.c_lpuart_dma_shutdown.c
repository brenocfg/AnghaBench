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
struct lpuart_port {int dma_tx_in_progress; int /*<<< orphan*/  dma_tx_chan; int /*<<< orphan*/  dma_wait; scalar_t__ lpuart_dma_tx_use; int /*<<< orphan*/  port; int /*<<< orphan*/  lpuart_timer; scalar_t__ lpuart_dma_rx_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart_dma_rx_free (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpuart_dma_shutdown(struct lpuart_port *sport)
{
	if (sport->lpuart_dma_rx_use) {
		del_timer_sync(&sport->lpuart_timer);
		lpuart_dma_rx_free(&sport->port);
	}

	if (sport->lpuart_dma_tx_use) {
		if (wait_event_interruptible(sport->dma_wait,
			!sport->dma_tx_in_progress) != false) {
			sport->dma_tx_in_progress = false;
			dmaengine_terminate_all(sport->dma_tx_chan);
		}
	}
}