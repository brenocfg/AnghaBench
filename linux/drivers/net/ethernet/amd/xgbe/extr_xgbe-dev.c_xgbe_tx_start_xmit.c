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
struct xgbe_ring_data {int /*<<< orphan*/  rdesc_dma; } ;
struct TYPE_2__ {scalar_t__ xmit_more; } ;
struct xgbe_ring {TYPE_1__ tx; int /*<<< orphan*/  cur; } ;
struct xgbe_prv_data {scalar_t__ tx_usecs; } ;
struct xgbe_channel {int tx_timer_active; int /*<<< orphan*/  tx_timer; struct xgbe_prv_data* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_TDTR_LO ; 
 struct xgbe_ring_data* XGBE_GET_DESC_DATA (struct xgbe_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE (struct xgbe_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ usecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void xgbe_tx_start_xmit(struct xgbe_channel *channel,
			       struct xgbe_ring *ring)
{
	struct xgbe_prv_data *pdata = channel->pdata;
	struct xgbe_ring_data *rdata;

	/* Make sure everything is written before the register write */
	wmb();

	/* Issue a poll command to Tx DMA by writing address
	 * of next immediate free descriptor */
	rdata = XGBE_GET_DESC_DATA(ring, ring->cur);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_TDTR_LO,
			  lower_32_bits(rdata->rdesc_dma));

	/* Start the Tx timer */
	if (pdata->tx_usecs && !channel->tx_timer_active) {
		channel->tx_timer_active = 1;
		mod_timer(&channel->tx_timer,
			  jiffies + usecs_to_jiffies(pdata->tx_usecs));
	}

	ring->tx.xmit_more = 0;
}