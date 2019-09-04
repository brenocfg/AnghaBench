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
struct vnic_wq {int dummy; } ;
struct sk_buff {unsigned int len; unsigned int csum_offset; int /*<<< orphan*/  data; } ;
struct enic {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  enic_dma_map_check (struct enic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enic_queue_wq_desc_csum_l4 (struct vnic_wq*,struct sk_buff*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int,unsigned int,int,int) ; 
 int enic_queue_wq_skb_cont (struct enic*,struct vnic_wq*,struct sk_buff*,unsigned int,int) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_checksum_start_offset (struct sk_buff*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_queue_wq_skb_csum_l4(struct enic *enic, struct vnic_wq *wq,
				     struct sk_buff *skb, int vlan_tag_insert,
				     unsigned int vlan_tag, int loopback)
{
	unsigned int head_len = skb_headlen(skb);
	unsigned int len_left = skb->len - head_len;
	unsigned int hdr_len = skb_checksum_start_offset(skb);
	unsigned int csum_offset = hdr_len + skb->csum_offset;
	int eop = (len_left == 0);
	dma_addr_t dma_addr;
	int err = 0;

	dma_addr = pci_map_single(enic->pdev, skb->data, head_len,
				  PCI_DMA_TODEVICE);
	if (unlikely(enic_dma_map_check(enic, dma_addr)))
		return -ENOMEM;

	/* Queue the main skb fragment. The fragments are no larger
	 * than max MTU(9000)+ETH_HDR_LEN(14) bytes, which is less
	 * than WQ_ENET_MAX_DESC_LEN length. So only one descriptor
	 * per fragment is queued.
	 */
	enic_queue_wq_desc_csum_l4(wq, skb, dma_addr, head_len,	csum_offset,
				   hdr_len, vlan_tag_insert, vlan_tag, eop,
				   loopback);

	if (!eop)
		err = enic_queue_wq_skb_cont(enic, wq, skb, len_left, loopback);

	return err;
}