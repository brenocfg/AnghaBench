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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct dma_channel {scalar_t__ status; scalar_t__ actual_len; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MUSB_DMA_STATUS_BUSY ; 
 scalar_t__ MUSB_DMA_STATUS_FREE ; 
 scalar_t__ MUSB_DMA_STATUS_UNKNOWN ; 
 int ux500_configure_channel (struct dma_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ux500_dma_channel_program(struct dma_channel *channel,
				u16 packet_sz, u8 mode,
				dma_addr_t dma_addr, u32 len)
{
	int ret;

	BUG_ON(channel->status == MUSB_DMA_STATUS_UNKNOWN ||
		channel->status == MUSB_DMA_STATUS_BUSY);

	channel->status = MUSB_DMA_STATUS_BUSY;
	channel->actual_len = 0;
	ret = ux500_configure_channel(channel, packet_sz, mode, dma_addr, len);
	if (!ret)
		channel->status = MUSB_DMA_STATUS_FREE;

	return ret;
}