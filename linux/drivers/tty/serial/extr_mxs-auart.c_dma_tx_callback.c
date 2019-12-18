#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* state; } ;
struct mxs_auart_port {TYPE_2__ port; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_sgl; int /*<<< orphan*/  dev; } ;
struct circ_buf {int dummy; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  MXS_AUART_DMA_TX_SYNC ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_auart_tx_chars (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_2__*) ; 

__attribute__((used)) static void dma_tx_callback(void *param)
{
	struct mxs_auart_port *s = param;
	struct circ_buf *xmit = &s->port.state->xmit;

	dma_unmap_sg(s->dev, &s->tx_sgl, 1, DMA_TO_DEVICE);

	/* clear the bit used to serialize the DMA tx. */
	clear_bit(MXS_AUART_DMA_TX_SYNC, &s->flags);
	smp_mb__after_atomic();

	/* wake up the possible processes. */
	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&s->port);

	mxs_auart_tx_chars(s);
}