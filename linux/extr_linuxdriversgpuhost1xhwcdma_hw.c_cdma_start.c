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
struct host1x_channel {int dummy; } ;
struct TYPE_2__ {int pos; int dma; int size; } ;
struct host1x_cdma {int running; int last_pos; TYPE_1__ push_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_CHANNEL_DMACTRL ; 
 int HOST1X_CHANNEL_DMACTRL_DMAGETRST ; 
 int HOST1X_CHANNEL_DMACTRL_DMAINITGET ; 
 int HOST1X_CHANNEL_DMACTRL_DMASTOP ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMAEND ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMAPUT ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMASTART ; 
 struct host1x_channel* cdma_to_channel (struct host1x_cdma*) ; 
 int /*<<< orphan*/  host1x_ch_writel (struct host1x_channel*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdma_start(struct host1x_cdma *cdma)
{
	struct host1x_channel *ch = cdma_to_channel(cdma);

	if (cdma->running)
		return;

	cdma->last_pos = cdma->push_buffer.pos;

	host1x_ch_writel(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP,
			 HOST1X_CHANNEL_DMACTRL);

	/* set base, put and end pointer */
	host1x_ch_writel(ch, cdma->push_buffer.dma, HOST1X_CHANNEL_DMASTART);
	host1x_ch_writel(ch, cdma->push_buffer.pos, HOST1X_CHANNEL_DMAPUT);
	host1x_ch_writel(ch, cdma->push_buffer.dma + cdma->push_buffer.size + 4,
			 HOST1X_CHANNEL_DMAEND);

	/* reset GET */
	host1x_ch_writel(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP |
			 HOST1X_CHANNEL_DMACTRL_DMAGETRST |
			 HOST1X_CHANNEL_DMACTRL_DMAINITGET,
			 HOST1X_CHANNEL_DMACTRL);

	/* start the command DMA */
	host1x_ch_writel(ch, 0, HOST1X_CHANNEL_DMACTRL);

	cdma->running = true;
}