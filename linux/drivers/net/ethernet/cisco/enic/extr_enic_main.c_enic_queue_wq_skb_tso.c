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
struct vnic_wq {int dummy; } ;
struct sk_buff {unsigned int len; unsigned int data; scalar_t__ encapsulation; } ;
struct enic {TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ WQ_ENET_MAX_DESC_LEN ; 
 int /*<<< orphan*/  enic_dma_map_check (struct enic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enic_preload_tcp_csum (struct sk_buff*) ; 
 int /*<<< orphan*/  enic_preload_tcp_csum_encap (struct sk_buff*) ; 
 int /*<<< orphan*/  enic_queue_wq_desc_cont (struct vnic_wq*,struct sk_buff*,int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/  enic_queue_wq_desc_tso (struct vnic_wq*,struct sk_buff*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int,unsigned int,int,int) ; 
 scalar_t__ inner_tcp_hdrlen (struct sk_buff*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pci_map_single (TYPE_2__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 unsigned int skb_inner_transport_header (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 
 unsigned int tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_queue_wq_skb_tso(struct enic *enic, struct vnic_wq *wq,
				 struct sk_buff *skb, unsigned int mss,
				 int vlan_tag_insert, unsigned int vlan_tag,
				 int loopback)
{
	unsigned int frag_len_left = skb_headlen(skb);
	unsigned int len_left = skb->len - frag_len_left;
	int eop = (len_left == 0);
	unsigned int offset = 0;
	unsigned int hdr_len;
	dma_addr_t dma_addr;
	unsigned int len;
	skb_frag_t *frag;

	if (skb->encapsulation) {
		hdr_len = skb_inner_transport_header(skb) - skb->data;
		hdr_len += inner_tcp_hdrlen(skb);
		enic_preload_tcp_csum_encap(skb);
	} else {
		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		enic_preload_tcp_csum(skb);
	}

	/* Queue WQ_ENET_MAX_DESC_LEN length descriptors
	 * for the main skb fragment
	 */
	while (frag_len_left) {
		len = min(frag_len_left, (unsigned int)WQ_ENET_MAX_DESC_LEN);
		dma_addr = pci_map_single(enic->pdev, skb->data + offset, len,
					  PCI_DMA_TODEVICE);
		if (unlikely(enic_dma_map_check(enic, dma_addr)))
			return -ENOMEM;
		enic_queue_wq_desc_tso(wq, skb, dma_addr, len, mss, hdr_len,
				       vlan_tag_insert, vlan_tag,
				       eop && (len == frag_len_left), loopback);
		frag_len_left -= len;
		offset += len;
	}

	if (eop)
		return 0;

	/* Queue WQ_ENET_MAX_DESC_LEN length descriptors
	 * for additional data fragments
	 */
	for (frag = skb_shinfo(skb)->frags; len_left; frag++) {
		len_left -= skb_frag_size(frag);
		frag_len_left = skb_frag_size(frag);
		offset = 0;

		while (frag_len_left) {
			len = min(frag_len_left,
				(unsigned int)WQ_ENET_MAX_DESC_LEN);
			dma_addr = skb_frag_dma_map(&enic->pdev->dev, frag,
						    offset, len,
						    DMA_TO_DEVICE);
			if (unlikely(enic_dma_map_check(enic, dma_addr)))
				return -ENOMEM;
			enic_queue_wq_desc_cont(wq, skb, dma_addr, len,
						(len_left == 0) &&
						 (len == frag_len_left),/*EOP*/
						loopback);
			frag_len_left -= len;
			offset += len;
		}
	}

	return 0;
}