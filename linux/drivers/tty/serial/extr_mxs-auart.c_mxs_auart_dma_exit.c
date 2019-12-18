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
struct mxs_auart_port {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int AUART_CTRL2_DMAONERR ; 
 int AUART_CTRL2_RXDMAE ; 
 int AUART_CTRL2_TXDMAE ; 
 int /*<<< orphan*/  MXS_AUART_DMA_ENABLED ; 
 int /*<<< orphan*/  MXS_AUART_DMA_RX_READY ; 
 int /*<<< orphan*/  MXS_AUART_DMA_TX_SYNC ; 
 int /*<<< orphan*/  REG_CTRL2 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxs_auart_dma_exit_channel (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_clr (int,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxs_auart_dma_exit(struct mxs_auart_port *s)
{

	mxs_clr(AUART_CTRL2_TXDMAE | AUART_CTRL2_RXDMAE | AUART_CTRL2_DMAONERR,
		s, REG_CTRL2);

	mxs_auart_dma_exit_channel(s);
	s->flags &= ~MXS_AUART_DMA_ENABLED;
	clear_bit(MXS_AUART_DMA_TX_SYNC, &s->flags);
	clear_bit(MXS_AUART_DMA_RX_READY, &s->flags);
}