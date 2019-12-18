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
typedef  size_t u8 ;
struct ux500_dma_controller {TYPE_2__* tx_channel; TYPE_1__* rx_channel; } ;
struct ux500_dma_channel {scalar_t__ dma_chan; } ;
struct dma_channel {struct ux500_dma_channel* private_data; } ;
struct TYPE_4__ {struct dma_channel channel; } ;
struct TYPE_3__ {struct dma_channel channel; } ;

/* Variables and functions */
 size_t UX500_MUSB_DMA_NUM_RX_TX_CHANNELS ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  ux500_dma_channel_release (struct dma_channel*) ; 

__attribute__((used)) static void ux500_dma_controller_stop(struct ux500_dma_controller *controller)
{
	struct ux500_dma_channel *ux500_channel;
	struct dma_channel *channel;
	u8 ch_num;

	for (ch_num = 0; ch_num < UX500_MUSB_DMA_NUM_RX_TX_CHANNELS; ch_num++) {
		channel = &controller->rx_channel[ch_num].channel;
		ux500_channel = channel->private_data;

		ux500_dma_channel_release(channel);

		if (ux500_channel->dma_chan)
			dma_release_channel(ux500_channel->dma_chan);
	}

	for (ch_num = 0; ch_num < UX500_MUSB_DMA_NUM_RX_TX_CHANNELS; ch_num++) {
		channel = &controller->tx_channel[ch_num].channel;
		ux500_channel = channel->private_data;

		ux500_dma_channel_release(channel);

		if (ux500_channel->dma_chan)
			dma_release_channel(ux500_channel->dma_chan);
	}
}