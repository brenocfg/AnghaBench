#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct device {int dummy; } ;
struct bgmac_slot_info {int /*<<< orphan*/  dma_addr; struct bgmac_rx_header* buf; } ;
struct bgmac_rx_header {int /*<<< orphan*/  flags; int /*<<< orphan*/  len; } ;
struct bgmac_dma_ring {int start; struct bgmac_slot_info* slots; scalar_t__ index_base; scalar_t__ mmio_base; } ;
struct bgmac_dma_desc {int dummy; } ;
struct bgmac {int /*<<< orphan*/  napi; TYPE_2__* net_dev; struct device* dma_dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int BGMAC_DMA_RX_STATDPTR ; 
 scalar_t__ BGMAC_DMA_RX_STATUS ; 
 int BGMAC_RX_ALLOC_SIZE ; 
 int BGMAC_RX_BUF_OFFSET ; 
 int /*<<< orphan*/  BGMAC_RX_BUF_SIZE ; 
 int BGMAC_RX_FRAME_OFFSET ; 
 size_t BGMAC_RX_RING_SLOTS ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  bgmac_dma_rx_poison_buf (struct device*,struct bgmac_slot_info*) ; 
 int /*<<< orphan*/  bgmac_dma_rx_setup_desc (struct bgmac*,struct bgmac_dma_ring*,size_t) ; 
 scalar_t__ bgmac_dma_rx_skb_for_slot (struct bgmac*,struct bgmac_slot_info*) ; 
 int /*<<< orphan*/  bgmac_dma_rx_update_index (struct bgmac*,struct bgmac_dma_ring*) ; 
 int bgmac_read (struct bgmac*,scalar_t__) ; 
 struct sk_buff* build_skb (void*,int) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_head_page (void*) ; 

__attribute__((used)) static int bgmac_dma_rx_read(struct bgmac *bgmac, struct bgmac_dma_ring *ring,
			     int weight)
{
	u32 end_slot;
	int handled = 0;

	end_slot = bgmac_read(bgmac, ring->mmio_base + BGMAC_DMA_RX_STATUS);
	end_slot &= BGMAC_DMA_RX_STATDPTR;
	end_slot -= ring->index_base;
	end_slot &= BGMAC_DMA_RX_STATDPTR;
	end_slot /= sizeof(struct bgmac_dma_desc);

	while (ring->start != end_slot) {
		struct device *dma_dev = bgmac->dma_dev;
		struct bgmac_slot_info *slot = &ring->slots[ring->start];
		struct bgmac_rx_header *rx = slot->buf + BGMAC_RX_BUF_OFFSET;
		struct sk_buff *skb;
		void *buf = slot->buf;
		dma_addr_t dma_addr = slot->dma_addr;
		u16 len, flags;

		do {
			/* Prepare new skb as replacement */
			if (bgmac_dma_rx_skb_for_slot(bgmac, slot)) {
				bgmac_dma_rx_poison_buf(dma_dev, slot);
				break;
			}

			/* Unmap buffer to make it accessible to the CPU */
			dma_unmap_single(dma_dev, dma_addr,
					 BGMAC_RX_BUF_SIZE, DMA_FROM_DEVICE);

			/* Get info from the header */
			len = le16_to_cpu(rx->len);
			flags = le16_to_cpu(rx->flags);

			/* Check for poison and drop or pass the packet */
			if (len == 0xdead && flags == 0xbeef) {
				netdev_err(bgmac->net_dev, "Found poisoned packet at slot %d, DMA issue!\n",
					   ring->start);
				put_page(virt_to_head_page(buf));
				bgmac->net_dev->stats.rx_errors++;
				break;
			}

			if (len > BGMAC_RX_ALLOC_SIZE) {
				netdev_err(bgmac->net_dev, "Found oversized packet at slot %d, DMA issue!\n",
					   ring->start);
				put_page(virt_to_head_page(buf));
				bgmac->net_dev->stats.rx_length_errors++;
				bgmac->net_dev->stats.rx_errors++;
				break;
			}

			/* Omit CRC. */
			len -= ETH_FCS_LEN;

			skb = build_skb(buf, BGMAC_RX_ALLOC_SIZE);
			if (unlikely(!skb)) {
				netdev_err(bgmac->net_dev, "build_skb failed\n");
				put_page(virt_to_head_page(buf));
				bgmac->net_dev->stats.rx_errors++;
				break;
			}
			skb_put(skb, BGMAC_RX_FRAME_OFFSET +
				BGMAC_RX_BUF_OFFSET + len);
			skb_pull(skb, BGMAC_RX_FRAME_OFFSET +
				 BGMAC_RX_BUF_OFFSET);

			skb_checksum_none_assert(skb);
			skb->protocol = eth_type_trans(skb, bgmac->net_dev);
			bgmac->net_dev->stats.rx_bytes += len;
			bgmac->net_dev->stats.rx_packets++;
			napi_gro_receive(&bgmac->napi, skb);
			handled++;
		} while (0);

		bgmac_dma_rx_setup_desc(bgmac, ring, ring->start);

		if (++ring->start >= BGMAC_RX_RING_SLOTS)
			ring->start = 0;

		if (handled >= weight) /* Should never be greater */
			break;
	}

	bgmac_dma_rx_update_index(bgmac, ring);

	return handled;
}