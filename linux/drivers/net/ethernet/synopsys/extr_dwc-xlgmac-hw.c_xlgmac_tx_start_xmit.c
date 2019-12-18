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
struct TYPE_2__ {scalar_t__ xmit_more; } ;
struct xlgmac_ring {TYPE_1__ tx; int /*<<< orphan*/  cur; } ;
struct xlgmac_pdata {scalar_t__ tx_usecs; } ;
struct xlgmac_desc_data {int /*<<< orphan*/  dma_desc_addr; } ;
struct xlgmac_channel {int tx_timer_active; int /*<<< orphan*/  tx_timer; struct xlgmac_pdata* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_TDTR_LO ; 
 int /*<<< orphan*/  XLGMAC_DMA_REG (struct xlgmac_channel*,int /*<<< orphan*/ ) ; 
 struct xlgmac_desc_data* XLGMAC_GET_DESC_DATA (struct xlgmac_ring*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ usecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlgmac_tx_start_xmit(struct xlgmac_channel *channel,
				 struct xlgmac_ring *ring)
{
	struct xlgmac_pdata *pdata = channel->pdata;
	struct xlgmac_desc_data *desc_data;

	/* Make sure everything is written before the register write */
	wmb();

	/* Issue a poll command to Tx DMA by writing address
	 * of next immediate free descriptor
	 */
	desc_data = XLGMAC_GET_DESC_DATA(ring, ring->cur);
	writel(lower_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_TDTR_LO));

	/* Start the Tx timer */
	if (pdata->tx_usecs && !channel->tx_timer_active) {
		channel->tx_timer_active = 1;
		mod_timer(&channel->tx_timer,
			  jiffies + usecs_to_jiffies(pdata->tx_usecs));
	}

	ring->tx.xmit_more = 0;
}