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
struct TYPE_2__ {int /*<<< orphan*/  fifosize; } ;
struct mxs_auart_port {TYPE_1__ port; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; void* tx_dma_buf; void* tx_dma_chan; void* rx_dma_buf; void* rx_dma_chan; } ;

/* Variables and functions */
 int EINVAL ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  MXS_AUART_DMA_ENABLED ; 
 int /*<<< orphan*/  UART_XMIT_SIZE ; 
 scalar_t__ auart_dma_enabled (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 void* dma_request_slave_channel (int /*<<< orphan*/ ,char*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxs_auart_dma_exit_channel (struct mxs_auart_port*) ; 

__attribute__((used)) static int mxs_auart_dma_init(struct mxs_auart_port *s)
{
	if (auart_dma_enabled(s))
		return 0;

	/* init for RX */
	s->rx_dma_chan = dma_request_slave_channel(s->dev, "rx");
	if (!s->rx_dma_chan)
		goto err_out;
	s->rx_dma_buf = kzalloc(UART_XMIT_SIZE, GFP_KERNEL | GFP_DMA);
	if (!s->rx_dma_buf)
		goto err_out;

	/* init for TX */
	s->tx_dma_chan = dma_request_slave_channel(s->dev, "tx");
	if (!s->tx_dma_chan)
		goto err_out;
	s->tx_dma_buf = kzalloc(UART_XMIT_SIZE, GFP_KERNEL | GFP_DMA);
	if (!s->tx_dma_buf)
		goto err_out;

	/* set the flags */
	s->flags |= MXS_AUART_DMA_ENABLED;
	dev_dbg(s->dev, "enabled the DMA support.");

	/* The DMA buffer is now the FIFO the TTY subsystem can use */
	s->port.fifosize = UART_XMIT_SIZE;

	return 0;

err_out:
	mxs_auart_dma_exit_channel(s);
	return -EINVAL;

}