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
typedef  scalar_t__ u64 ;
struct host1x_channel {int dummy; } ;
struct TYPE_2__ {int pos; scalar_t__ size; scalar_t__ dma; } ;
struct host1x_cdma {int running; int last_pos; TYPE_1__ push_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_CHANNEL_DMACTRL ; 
 int HOST1X_CHANNEL_DMACTRL_DMAGETRST ; 
 int HOST1X_CHANNEL_DMACTRL_DMAINITGET ; 
 int HOST1X_CHANNEL_DMACTRL_DMASTOP ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMAEND ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMAEND_HI ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMAPUT ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMAPUT_HI ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMASTART ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMASTART_HI ; 
 struct host1x_channel* cdma_to_channel (struct host1x_cdma*) ; 
 int /*<<< orphan*/  host1x_ch_writel (struct host1x_channel*,int,int /*<<< orphan*/ ) ; 
 int lower_32_bits (scalar_t__) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void cdma_start(struct host1x_cdma *cdma)
{
	struct host1x_channel *ch = cdma_to_channel(cdma);
	u64 start, end;

	if (cdma->running)
		return;

	cdma->last_pos = cdma->push_buffer.pos;
	start = cdma->push_buffer.dma;
	end = cdma->push_buffer.size + 4;

	host1x_ch_writel(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP,
			 HOST1X_CHANNEL_DMACTRL);

	/* set base, put and end pointer */
	host1x_ch_writel(ch, lower_32_bits(start), HOST1X_CHANNEL_DMASTART);
#if HOST1X_HW >= 6
	host1x_ch_writel(ch, upper_32_bits(start), HOST1X_CHANNEL_DMASTART_HI);
#endif
	host1x_ch_writel(ch, cdma->push_buffer.pos, HOST1X_CHANNEL_DMAPUT);
#if HOST1X_HW >= 6
	host1x_ch_writel(ch, 0, HOST1X_CHANNEL_DMAPUT_HI);
#endif
	host1x_ch_writel(ch, lower_32_bits(end), HOST1X_CHANNEL_DMAEND);
#if HOST1X_HW >= 6
	host1x_ch_writel(ch, upper_32_bits(end), HOST1X_CHANNEL_DMAEND_HI);
#endif

	/* reset GET */
	host1x_ch_writel(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP |
			 HOST1X_CHANNEL_DMACTRL_DMAGETRST |
			 HOST1X_CHANNEL_DMACTRL_DMAINITGET,
			 HOST1X_CHANNEL_DMACTRL);

	/* start the command DMA */
	host1x_ch_writel(ch, 0, HOST1X_CHANNEL_DMACTRL);

	cdma->running = true;
}