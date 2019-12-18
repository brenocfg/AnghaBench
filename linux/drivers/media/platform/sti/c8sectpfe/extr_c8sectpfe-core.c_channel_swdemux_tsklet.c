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
typedef  int /*<<< orphan*/  u8 ;
struct channel_info {unsigned long back_buffer_busaddr; size_t demux_mapping; scalar_t__ irec; int /*<<< orphan*/  tsin_id; scalar_t__ back_buffer_aligned; struct c8sectpfei* fei; } ;
struct c8sectpfei {TYPE_2__** c8sectpfe; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* demux; } ;
struct TYPE_3__ {int /*<<< orphan*/  dvb_demux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ DMA_PRDS_BUSRP_TP (int /*<<< orphan*/ ) ; 
 scalar_t__ DMA_PRDS_BUSWP_TP (int /*<<< orphan*/ ) ; 
 unsigned long FEI_BUFFER_SIZE ; 
 int PACKET_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct channel_info*,int,int /*<<< orphan*/ *,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_packets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 unsigned long readl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void channel_swdemux_tsklet(unsigned long data)
{
	struct channel_info *channel = (struct channel_info *)data;
	struct c8sectpfei *fei;
	unsigned long wp, rp;
	int pos, num_packets, n, size;
	u8 *buf;

	if (unlikely(!channel || !channel->irec))
		return;

	fei = channel->fei;

	wp = readl(channel->irec + DMA_PRDS_BUSWP_TP(0));
	rp = readl(channel->irec + DMA_PRDS_BUSRP_TP(0));

	pos = rp - channel->back_buffer_busaddr;

	/* has it wrapped */
	if (wp < rp)
		wp = channel->back_buffer_busaddr + FEI_BUFFER_SIZE;

	size = wp - rp;
	num_packets = size / PACKET_SIZE;

	/* manage cache so data is visible to CPU */
	dma_sync_single_for_cpu(fei->dev,
				rp,
				size,
				DMA_FROM_DEVICE);

	buf = (u8 *) channel->back_buffer_aligned;

	dev_dbg(fei->dev,
		"chan=%d channel=%p num_packets = %d, buf = %p, pos = 0x%x\n\trp=0x%lx, wp=0x%lx\n",
		channel->tsin_id, channel, num_packets, buf, pos, rp, wp);

	for (n = 0; n < num_packets; n++) {
		dvb_dmx_swfilter_packets(
			&fei->c8sectpfe[0]->
				demux[channel->demux_mapping].dvb_demux,
			&buf[pos], 1);

		pos += PACKET_SIZE;
	}

	/* advance the read pointer */
	if (wp == (channel->back_buffer_busaddr + FEI_BUFFER_SIZE))
		writel(channel->back_buffer_busaddr, channel->irec +
			DMA_PRDS_BUSRP_TP(0));
	else
		writel(wp, channel->irec + DMA_PRDS_BUSRP_TP(0));
}