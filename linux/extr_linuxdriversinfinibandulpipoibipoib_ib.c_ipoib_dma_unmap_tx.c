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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct ipoib_tx_buf {int /*<<< orphan*/ * mapping; struct sk_buff* skb; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  ca; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ib_dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/  const*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

void ipoib_dma_unmap_tx(struct ipoib_dev_priv *priv,
			struct ipoib_tx_buf *tx_req)
{
	struct sk_buff *skb = tx_req->skb;
	u64 *mapping = tx_req->mapping;
	int i;
	int off;

	if (skb_headlen(skb)) {
		ib_dma_unmap_single(priv->ca, mapping[0], skb_headlen(skb),
				    DMA_TO_DEVICE);
		off = 1;
	} else
		off = 0;

	for (i = 0; i < skb_shinfo(skb)->nr_frags; ++i) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		ib_dma_unmap_page(priv->ca, mapping[i + off],
				  skb_frag_size(frag), DMA_TO_DEVICE);
	}
}