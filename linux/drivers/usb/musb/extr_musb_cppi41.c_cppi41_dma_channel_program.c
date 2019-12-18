#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct dma_channel {scalar_t__ status; scalar_t__ actual_len; struct cppi41_dma_channel* private_data; } ;
struct cppi41_dma_channel {TYPE_5__* hw_ep; scalar_t__ is_tx; TYPE_2__* controller; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_10__ {TYPE_4__* in_qh; TYPE_3__* out_qh; } ;
struct TYPE_9__ {int hb_mult; } ;
struct TYPE_8__ {int hb_mult; } ;
struct TYPE_6__ {int /*<<< orphan*/  musb; } ;
struct TYPE_7__ {TYPE_1__ controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MUSB_DMA_STATUS_BUSY ; 
 scalar_t__ MUSB_DMA_STATUS_FREE ; 
 scalar_t__ MUSB_DMA_STATUS_UNKNOWN ; 
 int cppi41_configure_channel (struct dma_channel*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_host_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cppi41_dma_channel_program(struct dma_channel *channel,
				u16 packet_sz, u8 mode,
				dma_addr_t dma_addr, u32 len)
{
	int ret;
	struct cppi41_dma_channel *cppi41_channel = channel->private_data;
	int hb_mult = 0;

	BUG_ON(channel->status == MUSB_DMA_STATUS_UNKNOWN ||
		channel->status == MUSB_DMA_STATUS_BUSY);

	if (is_host_active(cppi41_channel->controller->controller.musb)) {
		if (cppi41_channel->is_tx)
			hb_mult = cppi41_channel->hw_ep->out_qh->hb_mult;
		else
			hb_mult = cppi41_channel->hw_ep->in_qh->hb_mult;
	}

	channel->status = MUSB_DMA_STATUS_BUSY;
	channel->actual_len = 0;

	if (hb_mult)
		packet_sz = hb_mult * (packet_sz & 0x7FF);

	ret = cppi41_configure_channel(channel, packet_sz, mode, dma_addr, len);
	if (!ret)
		channel->status = MUSB_DMA_STATUS_FREE;

	return ret;
}