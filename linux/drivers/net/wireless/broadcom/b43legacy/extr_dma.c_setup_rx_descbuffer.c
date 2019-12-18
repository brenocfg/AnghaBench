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
struct sk_buff {scalar_t__ data; } ;
struct b43legacy_rxhdr_fw3 {scalar_t__ frame_len; } ;
struct b43legacy_hwtxstatus {scalar_t__ cookie; } ;
struct b43legacy_dmaring {int /*<<< orphan*/  rx_buffersize; int /*<<< orphan*/  tx; } ;
struct b43legacy_dmadesc_meta {int /*<<< orphan*/  dmaaddr; struct sk_buff* skb; } ;
struct b43legacy_dmadesc32 {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_DMA ; 
 struct sk_buff* __dev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ b43legacy_dma_mapping_error (struct b43legacy_dmaring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  map_descbuffer (struct b43legacy_dmaring*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op32_fill_descriptor (struct b43legacy_dmaring*,struct b43legacy_dmadesc32*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int setup_rx_descbuffer(struct b43legacy_dmaring *ring,
			       struct b43legacy_dmadesc32 *desc,
			       struct b43legacy_dmadesc_meta *meta,
			       gfp_t gfp_flags)
{
	struct b43legacy_rxhdr_fw3 *rxhdr;
	struct b43legacy_hwtxstatus *txstat;
	dma_addr_t dmaaddr;
	struct sk_buff *skb;

	B43legacy_WARN_ON(ring->tx);

	skb = __dev_alloc_skb(ring->rx_buffersize, gfp_flags);
	if (unlikely(!skb))
		return -ENOMEM;
	dmaaddr = map_descbuffer(ring, skb->data,
				 ring->rx_buffersize, 0);
	if (b43legacy_dma_mapping_error(ring, dmaaddr, ring->rx_buffersize, 0)) {
		/* ugh. try to realloc in zone_dma */
		gfp_flags |= GFP_DMA;

		dev_kfree_skb_any(skb);

		skb = __dev_alloc_skb(ring->rx_buffersize, gfp_flags);
		if (unlikely(!skb))
			return -ENOMEM;
		dmaaddr = map_descbuffer(ring, skb->data,
					 ring->rx_buffersize, 0);
	}

	if (b43legacy_dma_mapping_error(ring, dmaaddr, ring->rx_buffersize, 0)) {
		dev_kfree_skb_any(skb);
		return -EIO;
	}

	meta->skb = skb;
	meta->dmaaddr = dmaaddr;
	op32_fill_descriptor(ring, desc, dmaaddr, ring->rx_buffersize, 0, 0, 0);

	rxhdr = (struct b43legacy_rxhdr_fw3 *)(skb->data);
	rxhdr->frame_len = 0;
	txstat = (struct b43legacy_hwtxstatus *)(skb->data);
	txstat->cookie = 0;

	return 0;
}