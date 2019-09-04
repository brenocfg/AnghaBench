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
struct TYPE_7__ {int /*<<< orphan*/  status_error; int /*<<< orphan*/  vlan; int /*<<< orphan*/  length; } ;
struct TYPE_5__ {int /*<<< orphan*/  rss; } ;
struct TYPE_6__ {TYPE_1__ hi_dword; } ;
struct TYPE_8__ {TYPE_3__ upper; TYPE_2__ lower; } ;
union e1000_rx_desc_extended {TYPE_4__ wb; } ;
typedef  int u32 ;
struct sk_buff {union e1000_rx_desc_extended* data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int features; } ;
struct e1000_ring {unsigned int next_to_clean; unsigned int count; struct e1000_buffer* buffer_info; struct e1000_adapter* adapter; } ;
struct e1000_hw {int dummy; } ;
struct e1000_buffer {struct sk_buff* skb; scalar_t__ dma; } ;
struct e1000_adapter {int flags2; unsigned int total_rx_bytes; unsigned int total_rx_packets; int /*<<< orphan*/  (* alloc_rx_buf ) (struct e1000_ring*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_buffer_len; struct e1000_hw hw; struct pci_dev* pdev; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int E1000_RXDEXT_ERR_FRAME_ERR_MASK ; 
 int E1000_RXD_STAT_DD ; 
 int E1000_RXD_STAT_EOP ; 
 int E1000_RX_BUFFER_WRITE ; 
 union e1000_rx_desc_extended* E1000_RX_DESC_EXT (struct e1000_ring,unsigned int) ; 
 int FLAG2_CRC_STRIPPING ; 
 int FLAG2_IS_DISCARDING ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETIF_F_RXALL ; 
 int NETIF_F_RXFCS ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 int copybreak ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int e1000_desc_unused (struct e1000_ring*) ; 
 int /*<<< orphan*/  e1000_receive_skb (struct e1000_adapter*,struct net_device*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_rx_checksum (struct e1000_adapter*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  e1000_rx_hash (struct net_device*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prefetch (union e1000_rx_desc_extended*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int /*<<< orphan*/ ,union e1000_rx_desc_extended*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_ring*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct e1000_ring*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool e1000_clean_rx_irq(struct e1000_ring *rx_ring, int *work_done,
			       int work_to_do)
{
	struct e1000_adapter *adapter = rx_ring->adapter;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_hw *hw = &adapter->hw;
	union e1000_rx_desc_extended *rx_desc, *next_rxd;
	struct e1000_buffer *buffer_info, *next_buffer;
	u32 length, staterr;
	unsigned int i;
	int cleaned_count = 0;
	bool cleaned = false;
	unsigned int total_rx_bytes = 0, total_rx_packets = 0;

	i = rx_ring->next_to_clean;
	rx_desc = E1000_RX_DESC_EXT(*rx_ring, i);
	staterr = le32_to_cpu(rx_desc->wb.upper.status_error);
	buffer_info = &rx_ring->buffer_info[i];

	while (staterr & E1000_RXD_STAT_DD) {
		struct sk_buff *skb;

		if (*work_done >= work_to_do)
			break;
		(*work_done)++;
		dma_rmb();	/* read descriptor and rx_buffer_info after status DD */

		skb = buffer_info->skb;
		buffer_info->skb = NULL;

		prefetch(skb->data - NET_IP_ALIGN);

		i++;
		if (i == rx_ring->count)
			i = 0;
		next_rxd = E1000_RX_DESC_EXT(*rx_ring, i);
		prefetch(next_rxd);

		next_buffer = &rx_ring->buffer_info[i];

		cleaned = true;
		cleaned_count++;
		dma_unmap_single(&pdev->dev, buffer_info->dma,
				 adapter->rx_buffer_len, DMA_FROM_DEVICE);
		buffer_info->dma = 0;

		length = le16_to_cpu(rx_desc->wb.upper.length);

		/* !EOP means multiple descriptors were used to store a single
		 * packet, if that's the case we need to toss it.  In fact, we
		 * need to toss every packet with the EOP bit clear and the
		 * next frame that _does_ have the EOP bit set, as it is by
		 * definition only a frame fragment
		 */
		if (unlikely(!(staterr & E1000_RXD_STAT_EOP)))
			adapter->flags2 |= FLAG2_IS_DISCARDING;

		if (adapter->flags2 & FLAG2_IS_DISCARDING) {
			/* All receives must fit into a single buffer */
			e_dbg("Receive packet consumed multiple buffers\n");
			/* recycle */
			buffer_info->skb = skb;
			if (staterr & E1000_RXD_STAT_EOP)
				adapter->flags2 &= ~FLAG2_IS_DISCARDING;
			goto next_desc;
		}

		if (unlikely((staterr & E1000_RXDEXT_ERR_FRAME_ERR_MASK) &&
			     !(netdev->features & NETIF_F_RXALL))) {
			/* recycle */
			buffer_info->skb = skb;
			goto next_desc;
		}

		/* adjust length to remove Ethernet CRC */
		if (!(adapter->flags2 & FLAG2_CRC_STRIPPING)) {
			/* If configured to store CRC, don't subtract FCS,
			 * but keep the FCS bytes out of the total_rx_bytes
			 * counter
			 */
			if (netdev->features & NETIF_F_RXFCS)
				total_rx_bytes -= 4;
			else
				length -= 4;
		}

		total_rx_bytes += length;
		total_rx_packets++;

		/* code added for copybreak, this should improve
		 * performance for small packets with large amounts
		 * of reassembly being done in the stack
		 */
		if (length < copybreak) {
			struct sk_buff *new_skb =
				napi_alloc_skb(&adapter->napi, length);
			if (new_skb) {
				skb_copy_to_linear_data_offset(new_skb,
							       -NET_IP_ALIGN,
							       (skb->data -
								NET_IP_ALIGN),
							       (length +
								NET_IP_ALIGN));
				/* save the skb in buffer_info as good */
				buffer_info->skb = skb;
				skb = new_skb;
			}
			/* else just continue with the old one */
		}
		/* end copybreak code */
		skb_put(skb, length);

		/* Receive Checksum Offload */
		e1000_rx_checksum(adapter, staterr, skb);

		e1000_rx_hash(netdev, rx_desc->wb.lower.hi_dword.rss, skb);

		e1000_receive_skb(adapter, netdev, skb, staterr,
				  rx_desc->wb.upper.vlan);

next_desc:
		rx_desc->wb.upper.status_error &= cpu_to_le32(~0xFF);

		/* return some buffers to hardware, one at a time is too slow */
		if (cleaned_count >= E1000_RX_BUFFER_WRITE) {
			adapter->alloc_rx_buf(rx_ring, cleaned_count,
					      GFP_ATOMIC);
			cleaned_count = 0;
		}

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;

		staterr = le32_to_cpu(rx_desc->wb.upper.status_error);
	}
	rx_ring->next_to_clean = i;

	cleaned_count = e1000_desc_unused(rx_ring);
	if (cleaned_count)
		adapter->alloc_rx_buf(rx_ring, cleaned_count, GFP_ATOMIC);

	adapter->total_rx_bytes += total_rx_bytes;
	adapter->total_rx_packets += total_rx_packets;
	return cleaned;
}