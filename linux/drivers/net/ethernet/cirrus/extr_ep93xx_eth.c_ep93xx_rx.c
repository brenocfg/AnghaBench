#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_6__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_errors; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_3__ stats; TYPE_2__ dev; } ;
struct ep93xx_rstat {int rstat0; int rstat1; } ;
struct ep93xx_rdesc {int /*<<< orphan*/  buf_addr; } ;
struct ep93xx_priv {int rx_pointer; int /*<<< orphan*/  napi; int /*<<< orphan*/ * rx_buf; TYPE_1__* descs; } ;
struct TYPE_4__ {struct ep93xx_rdesc* rdesc; struct ep93xx_rstat* rstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int MAX_PKT_SIZE ; 
 int RSTAT0_CRCE ; 
 int RSTAT0_CRCI ; 
 int RSTAT0_EDATA ; 
 int RSTAT0_EOB ; 
 int RSTAT0_EOF ; 
 int RSTAT0_FE ; 
 int RSTAT0_OE ; 
 int RSTAT0_RFP ; 
 int RSTAT0_RUNT ; 
 int RSTAT0_RWE ; 
 int RSTAT1_BUFFER_INDEX ; 
 int RSTAT1_FRAME_LENGTH ; 
 int RSTAT1_RFP ; 
 int RX_QUEUE_ENTRIES ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 struct ep93xx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_crit (char*,int,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int ep93xx_rx(struct net_device *dev, int budget)
{
	struct ep93xx_priv *ep = netdev_priv(dev);
	int processed = 0;

	while (processed < budget) {
		int entry;
		struct ep93xx_rstat *rstat;
		u32 rstat0;
		u32 rstat1;
		int length;
		struct sk_buff *skb;

		entry = ep->rx_pointer;
		rstat = ep->descs->rstat + entry;

		rstat0 = rstat->rstat0;
		rstat1 = rstat->rstat1;
		if (!(rstat0 & RSTAT0_RFP) || !(rstat1 & RSTAT1_RFP))
			break;

		rstat->rstat0 = 0;
		rstat->rstat1 = 0;

		if (!(rstat0 & RSTAT0_EOF))
			pr_crit("not end-of-frame %.8x %.8x\n", rstat0, rstat1);
		if (!(rstat0 & RSTAT0_EOB))
			pr_crit("not end-of-buffer %.8x %.8x\n", rstat0, rstat1);
		if ((rstat1 & RSTAT1_BUFFER_INDEX) >> 16 != entry)
			pr_crit("entry mismatch %.8x %.8x\n", rstat0, rstat1);

		if (!(rstat0 & RSTAT0_RWE)) {
			dev->stats.rx_errors++;
			if (rstat0 & RSTAT0_OE)
				dev->stats.rx_fifo_errors++;
			if (rstat0 & RSTAT0_FE)
				dev->stats.rx_frame_errors++;
			if (rstat0 & (RSTAT0_RUNT | RSTAT0_EDATA))
				dev->stats.rx_length_errors++;
			if (rstat0 & RSTAT0_CRCE)
				dev->stats.rx_crc_errors++;
			goto err;
		}

		length = rstat1 & RSTAT1_FRAME_LENGTH;
		if (length > MAX_PKT_SIZE) {
			pr_notice("invalid length %.8x %.8x\n", rstat0, rstat1);
			goto err;
		}

		/* Strip FCS.  */
		if (rstat0 & RSTAT0_CRCI)
			length -= 4;

		skb = netdev_alloc_skb(dev, length + 2);
		if (likely(skb != NULL)) {
			struct ep93xx_rdesc *rxd = &ep->descs->rdesc[entry];
			skb_reserve(skb, 2);
			dma_sync_single_for_cpu(dev->dev.parent, rxd->buf_addr,
						length, DMA_FROM_DEVICE);
			skb_copy_to_linear_data(skb, ep->rx_buf[entry], length);
			dma_sync_single_for_device(dev->dev.parent,
						   rxd->buf_addr, length,
						   DMA_FROM_DEVICE);
			skb_put(skb, length);
			skb->protocol = eth_type_trans(skb, dev);

			napi_gro_receive(&ep->napi, skb);

			dev->stats.rx_packets++;
			dev->stats.rx_bytes += length;
		} else {
			dev->stats.rx_dropped++;
		}

err:
		ep->rx_pointer = (entry + 1) & (RX_QUEUE_ENTRIES - 1);
		processed++;
	}

	return processed;
}