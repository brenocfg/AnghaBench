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
struct imx_port {int /*<<< orphan*/ * dma_chan_tx; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  rx_cookie; int /*<<< orphan*/ * dma_chan_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void imx_uart_dma_exit(struct imx_port *sport)
{
	if (sport->dma_chan_rx) {
		dmaengine_terminate_sync(sport->dma_chan_rx);
		dma_release_channel(sport->dma_chan_rx);
		sport->dma_chan_rx = NULL;
		sport->rx_cookie = -EINVAL;
		kfree(sport->rx_buf);
		sport->rx_buf = NULL;
	}

	if (sport->dma_chan_tx) {
		dmaengine_terminate_sync(sport->dma_chan_tx);
		dma_release_channel(sport->dma_chan_tx);
		sport->dma_chan_tx = NULL;
	}
}