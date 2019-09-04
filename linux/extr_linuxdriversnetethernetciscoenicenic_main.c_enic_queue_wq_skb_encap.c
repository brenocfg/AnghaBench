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
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; } ;
struct enic {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  WQ_ENET_OFFLOAD_MODE_CSUM ; 
 int /*<<< orphan*/  enic_dma_map_check (struct enic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enic_queue_wq_desc_ex (struct vnic_wq*,struct sk_buff*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int enic_queue_wq_skb_cont (struct enic*,struct vnic_wq*,struct sk_buff*,unsigned int,int) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int enic_queue_wq_skb_encap(struct enic *enic, struct vnic_wq *wq,
					  struct sk_buff *skb,
					  int vlan_tag_insert,
					  unsigned int vlan_tag, int loopback)
{
	unsigned int head_len = skb_headlen(skb);
	unsigned int len_left = skb->len - head_len;
	/* Hardware will overwrite the checksum fields, calculating from
	 * scratch and ignoring the value placed by software.
	 * Offload mode = 00
	 * mss[2], mss[1], mss[0] bits are set
	 */
	unsigned int mss_or_csum = 7;
	int eop = (len_left == 0);
	dma_addr_t dma_addr;
	int err = 0;

	dma_addr = pci_map_single(enic->pdev, skb->data, head_len,
				  PCI_DMA_TODEVICE);
	if (unlikely(enic_dma_map_check(enic, dma_addr)))
		return -ENOMEM;

	enic_queue_wq_desc_ex(wq, skb, dma_addr, head_len, mss_or_csum, 0,
			      vlan_tag_insert, vlan_tag,
			      WQ_ENET_OFFLOAD_MODE_CSUM, eop, 1 /* SOP */, eop,
			      loopback);
	if (!eop)
		err = enic_queue_wq_skb_cont(enic, wq, skb, len_left, loopback);

	return err;
}