#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; } ;
struct page {int dummy; } ;
struct netcp_intf {int /*<<< orphan*/  ndev_dev; int /*<<< orphan*/  tx_pool; struct device* dev; } ;
struct knav_dma_desc {scalar_t__ desc_info; scalar_t__ next_desc; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_3__ {int nr_frags; scalar_t__ frag_list; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ IS_ERR_OR_NULL (struct knav_dma_desc*) ; 
 unsigned int KNAV_DMA_DESC_PKT_LEN_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dma_map_page (struct device*,struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 struct knav_dma_desc* knav_pool_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_pool_desc_map (int /*<<< orphan*/ ,struct knav_dma_desc*,int,scalar_t__*,unsigned int*) ; 
 scalar_t__ knav_pool_desc_virt_to_dma (int /*<<< orphan*/ ,struct knav_dma_desc*) ; 
 int /*<<< orphan*/  netcp_free_tx_desc_chain (struct netcp_intf*,struct knav_dma_desc*,int) ; 
 int /*<<< orphan*/  prefetchw (TYPE_1__*) ; 
 int /*<<< orphan*/  set_pkt_info (scalar_t__,unsigned int,int /*<<< orphan*/ ,struct knav_dma_desc*) ; 
 int /*<<< orphan*/  set_words (unsigned int*,int,scalar_t__*) ; 
 unsigned int skb_frag_off (int /*<<< orphan*/ *) ; 
 struct page* skb_frag_page (int /*<<< orphan*/ *) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct knav_dma_desc*
netcp_tx_map_skb(struct sk_buff *skb, struct netcp_intf *netcp)
{
	struct knav_dma_desc *desc, *ndesc, *pdesc;
	unsigned int pkt_len = skb_headlen(skb);
	struct device *dev = netcp->dev;
	dma_addr_t dma_addr;
	unsigned int dma_sz;
	int i;

	/* Map the linear buffer */
	dma_addr = dma_map_single(dev, skb->data, pkt_len, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(dev, dma_addr))) {
		dev_err(netcp->ndev_dev, "Failed to map skb buffer\n");
		return NULL;
	}

	desc = knav_pool_desc_get(netcp->tx_pool);
	if (IS_ERR_OR_NULL(desc)) {
		dev_err(netcp->ndev_dev, "out of TX desc\n");
		dma_unmap_single(dev, dma_addr, pkt_len, DMA_TO_DEVICE);
		return NULL;
	}

	set_pkt_info(dma_addr, pkt_len, 0, desc);
	if (skb_is_nonlinear(skb)) {
		prefetchw(skb_shinfo(skb));
	} else {
		desc->next_desc = 0;
		goto upd_pkt_len;
	}

	pdesc = desc;

	/* Handle the case where skb is fragmented in pages */
	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		struct page *page = skb_frag_page(frag);
		u32 page_offset = skb_frag_off(frag);
		u32 buf_len = skb_frag_size(frag);
		dma_addr_t desc_dma;
		u32 desc_dma_32;

		dma_addr = dma_map_page(dev, page, page_offset, buf_len,
					DMA_TO_DEVICE);
		if (unlikely(!dma_addr)) {
			dev_err(netcp->ndev_dev, "Failed to map skb page\n");
			goto free_descs;
		}

		ndesc = knav_pool_desc_get(netcp->tx_pool);
		if (IS_ERR_OR_NULL(ndesc)) {
			dev_err(netcp->ndev_dev, "out of TX desc for frags\n");
			dma_unmap_page(dev, dma_addr, buf_len, DMA_TO_DEVICE);
			goto free_descs;
		}

		desc_dma = knav_pool_desc_virt_to_dma(netcp->tx_pool, ndesc);
		set_pkt_info(dma_addr, buf_len, 0, ndesc);
		desc_dma_32 = (u32)desc_dma;
		set_words(&desc_dma_32, 1, &pdesc->next_desc);
		pkt_len += buf_len;
		if (pdesc != desc)
			knav_pool_desc_map(netcp->tx_pool, pdesc,
					   sizeof(*pdesc), &desc_dma, &dma_sz);
		pdesc = ndesc;
	}
	if (pdesc != desc)
		knav_pool_desc_map(netcp->tx_pool, pdesc, sizeof(*pdesc),
				   &dma_addr, &dma_sz);

	/* frag list based linkage is not supported for now. */
	if (skb_shinfo(skb)->frag_list) {
		dev_err_ratelimited(netcp->ndev_dev, "NETIF_F_FRAGLIST not supported\n");
		goto free_descs;
	}

upd_pkt_len:
	WARN_ON(pkt_len != skb->len);

	pkt_len &= KNAV_DMA_DESC_PKT_LEN_MASK;
	set_words(&pkt_len, 1, &desc->desc_info);
	return desc;

free_descs:
	netcp_free_tx_desc_chain(netcp, desc, sizeof(*desc));
	return NULL;
}