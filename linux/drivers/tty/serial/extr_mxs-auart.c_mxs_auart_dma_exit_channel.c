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
struct mxs_auart_port {int /*<<< orphan*/ * rx_dma_buf; int /*<<< orphan*/ * tx_dma_buf; int /*<<< orphan*/ * rx_dma_chan; int /*<<< orphan*/ * tx_dma_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mxs_auart_dma_exit_channel(struct mxs_auart_port *s)
{
	if (s->tx_dma_chan) {
		dma_release_channel(s->tx_dma_chan);
		s->tx_dma_chan = NULL;
	}
	if (s->rx_dma_chan) {
		dma_release_channel(s->rx_dma_chan);
		s->rx_dma_chan = NULL;
	}

	kfree(s->tx_dma_buf);
	kfree(s->rx_dma_buf);
	s->tx_dma_buf = NULL;
	s->rx_dma_buf = NULL;
}