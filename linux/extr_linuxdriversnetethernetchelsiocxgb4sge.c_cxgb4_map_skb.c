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
struct skb_shared_info {size_t nr_frags; int /*<<< orphan*/ * frags; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_dma_map (struct device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff const*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff const*) ; 

int cxgb4_map_skb(struct device *dev, const struct sk_buff *skb,
		  dma_addr_t *addr)
{
	const skb_frag_t *fp, *end;
	const struct skb_shared_info *si;

	*addr = dma_map_single(dev, skb->data, skb_headlen(skb), DMA_TO_DEVICE);
	if (dma_mapping_error(dev, *addr))
		goto out_err;

	si = skb_shinfo(skb);
	end = &si->frags[si->nr_frags];

	for (fp = si->frags; fp < end; fp++) {
		*++addr = skb_frag_dma_map(dev, fp, 0, skb_frag_size(fp),
					   DMA_TO_DEVICE);
		if (dma_mapping_error(dev, *addr))
			goto unwind;
	}
	return 0;

unwind:
	while (fp-- > si->frags)
		dma_unmap_page(dev, *--addr, skb_frag_size(fp), DMA_TO_DEVICE);

	dma_unmap_single(dev, addr[-1], skb_headlen(skb), DMA_TO_DEVICE);
out_err:
	return -ENOMEM;
}