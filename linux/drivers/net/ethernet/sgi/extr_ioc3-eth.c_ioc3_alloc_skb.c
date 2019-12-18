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
struct ioc3_private {int /*<<< orphan*/  dma_dev; } ;
struct ioc3_erxbuf {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IOC3_DMA_XFER_LEN ; 
 scalar_t__ RX_BUF_SIZE ; 
 int RX_OFFSET ; 
 int aligned_rx_skb_addr (unsigned long) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static inline int ioc3_alloc_skb(struct ioc3_private *ip, struct sk_buff **skb,
				 struct ioc3_erxbuf **rxb, dma_addr_t *rxb_dma)
{
	struct sk_buff *new_skb;
	dma_addr_t d;
	int offset;

	new_skb = alloc_skb(RX_BUF_SIZE + IOC3_DMA_XFER_LEN - 1, GFP_ATOMIC);
	if (!new_skb)
		return -ENOMEM;

	/* ensure buffer is aligned to IOC3_DMA_XFER_LEN */
	offset = aligned_rx_skb_addr((unsigned long)new_skb->data);
	if (offset)
		skb_reserve(new_skb, offset);

	d = dma_map_single(ip->dma_dev, new_skb->data,
			   RX_BUF_SIZE, DMA_FROM_DEVICE);

	if (dma_mapping_error(ip->dma_dev, d)) {
		dev_kfree_skb_any(new_skb);
		return -ENOMEM;
	}
	*rxb_dma = d;
	*rxb = (struct ioc3_erxbuf *)new_skb->data;
	skb_reserve(new_skb, RX_OFFSET);
	*skb = new_skb;

	return 0;
}