#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; scalar_t__ ip_summed; scalar_t__ protocol; int* data; void* csum; } ;
struct pch_gbe_tx_ring {unsigned int next_to_use; unsigned int count; scalar_t__ dma; struct pch_gbe_buffer* buffer_info; } ;
struct pch_gbe_tx_desc {size_t length; size_t tx_words_eob; unsigned int tx_frame_ctrl; int /*<<< orphan*/  gbec_status; scalar_t__ buffer_addr; } ;
struct pch_gbe_hw {TYPE_2__* reg; } ;
struct pch_gbe_buffer {size_t length; int mapped; scalar_t__ dma; scalar_t__ time_stamp; struct sk_buff* skb; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; TYPE_1__* pdev; struct pch_gbe_hw hw; } ;
struct iphdr {scalar_t__ protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_8__ {void* check; } ;
struct TYPE_7__ {void* check; } ;
struct TYPE_6__ {int /*<<< orphan*/  TX_DSC_SW_P; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DSC_INIT16 ; 
 size_t ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ PCH_GBE_SHORT_PKT ; 
 unsigned int PCH_GBE_TXD_CTRL_APAD ; 
 unsigned int PCH_GBE_TXD_CTRL_TCPIP_ACC_OFF ; 
 struct pch_gbe_tx_desc* PCH_GBE_TX_DESC (struct pch_gbe_tx_ring,unsigned int) ; 
 void* csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,void*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,int /*<<< orphan*/ *) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pch_tx_timestamp (struct pch_gbe_adapter*,struct sk_buff*) ; 
 void* skb_checksum (struct sk_buff*,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 
 TYPE_4__* tcp_hdr (struct sk_buff*) ; 
 TYPE_3__* udp_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void pch_gbe_tx_queue(struct pch_gbe_adapter *adapter,
			      struct pch_gbe_tx_ring *tx_ring,
			      struct sk_buff *skb)
{
	struct pch_gbe_hw *hw = &adapter->hw;
	struct pch_gbe_tx_desc *tx_desc;
	struct pch_gbe_buffer *buffer_info;
	struct sk_buff *tmp_skb;
	unsigned int frame_ctrl;
	unsigned int ring_num;

	/*-- Set frame control --*/
	frame_ctrl = 0;
	if (unlikely(skb->len < PCH_GBE_SHORT_PKT))
		frame_ctrl |= PCH_GBE_TXD_CTRL_APAD;
	if (skb->ip_summed == CHECKSUM_NONE)
		frame_ctrl |= PCH_GBE_TXD_CTRL_TCPIP_ACC_OFF;

	/* Performs checksum processing */
	/*
	 * It is because the hardware accelerator does not support a checksum,
	 * when the received data size is less than 64 bytes.
	 */
	if (skb->len < PCH_GBE_SHORT_PKT && skb->ip_summed != CHECKSUM_NONE) {
		frame_ctrl |= PCH_GBE_TXD_CTRL_APAD |
			      PCH_GBE_TXD_CTRL_TCPIP_ACC_OFF;
		if (skb->protocol == htons(ETH_P_IP)) {
			struct iphdr *iph = ip_hdr(skb);
			unsigned int offset;
			offset = skb_transport_offset(skb);
			if (iph->protocol == IPPROTO_TCP) {
				skb->csum = 0;
				tcp_hdr(skb)->check = 0;
				skb->csum = skb_checksum(skb, offset,
							 skb->len - offset, 0);
				tcp_hdr(skb)->check =
					csum_tcpudp_magic(iph->saddr,
							  iph->daddr,
							  skb->len - offset,
							  IPPROTO_TCP,
							  skb->csum);
			} else if (iph->protocol == IPPROTO_UDP) {
				skb->csum = 0;
				udp_hdr(skb)->check = 0;
				skb->csum =
					skb_checksum(skb, offset,
						     skb->len - offset, 0);
				udp_hdr(skb)->check =
					csum_tcpudp_magic(iph->saddr,
							  iph->daddr,
							  skb->len - offset,
							  IPPROTO_UDP,
							  skb->csum);
			}
		}
	}

	ring_num = tx_ring->next_to_use;
	if (unlikely((ring_num + 1) == tx_ring->count))
		tx_ring->next_to_use = 0;
	else
		tx_ring->next_to_use = ring_num + 1;


	buffer_info = &tx_ring->buffer_info[ring_num];
	tmp_skb = buffer_info->skb;

	/* [Header:14][payload] ---> [Header:14][paddong:2][payload]    */
	memcpy(tmp_skb->data, skb->data, ETH_HLEN);
	tmp_skb->data[ETH_HLEN] = 0x00;
	tmp_skb->data[ETH_HLEN + 1] = 0x00;
	tmp_skb->len = skb->len;
	memcpy(&tmp_skb->data[ETH_HLEN + 2], &skb->data[ETH_HLEN],
	       (skb->len - ETH_HLEN));
	/*-- Set Buffer information --*/
	buffer_info->length = tmp_skb->len;
	buffer_info->dma = dma_map_single(&adapter->pdev->dev, tmp_skb->data,
					  buffer_info->length,
					  DMA_TO_DEVICE);
	if (dma_mapping_error(&adapter->pdev->dev, buffer_info->dma)) {
		netdev_err(adapter->netdev, "TX DMA map failed\n");
		buffer_info->dma = 0;
		buffer_info->time_stamp = 0;
		tx_ring->next_to_use = ring_num;
		return;
	}
	buffer_info->mapped = true;
	buffer_info->time_stamp = jiffies;

	/*-- Set Tx descriptor --*/
	tx_desc = PCH_GBE_TX_DESC(*tx_ring, ring_num);
	tx_desc->buffer_addr = (buffer_info->dma);
	tx_desc->length = (tmp_skb->len);
	tx_desc->tx_words_eob = ((tmp_skb->len + 3));
	tx_desc->tx_frame_ctrl = (frame_ctrl);
	tx_desc->gbec_status = (DSC_INIT16);

	if (unlikely(++ring_num == tx_ring->count))
		ring_num = 0;

	/* Update software pointer of TX descriptor */
	iowrite32(tx_ring->dma +
		  (int)sizeof(struct pch_gbe_tx_desc) * ring_num,
		  &hw->reg->TX_DSC_SW_P);

	pch_tx_timestamp(adapter, skb);

	dev_kfree_skb_any(skb);
}