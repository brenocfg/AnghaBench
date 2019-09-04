#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  status_error; int /*<<< orphan*/  vlan; int /*<<< orphan*/  length0; } ;
struct TYPE_9__ {int header_status; int /*<<< orphan*/ * length; } ;
struct TYPE_6__ {int /*<<< orphan*/  rss; } ;
struct TYPE_7__ {TYPE_1__ hi_dword; } ;
struct TYPE_10__ {TYPE_3__ middle; TYPE_4__ upper; TYPE_2__ lower; } ;
union e1000_rx_desc_packet_split {TYPE_5__ wb; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sk_buff {int data_len; scalar_t__ len; int /*<<< orphan*/  truesize; union e1000_rx_desc_packet_split* data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int features; } ;
struct e1000_ring {unsigned int next_to_clean; unsigned int count; struct e1000_buffer* buffer_info; struct e1000_adapter* adapter; } ;
struct e1000_ps_page {int /*<<< orphan*/ * page; scalar_t__ dma; } ;
struct e1000_hw {int dummy; } ;
struct e1000_buffer {struct sk_buff* skb; struct e1000_ps_page* ps_pages; scalar_t__ dma; } ;
struct e1000_adapter {int rx_ps_bsize0; int flags2; unsigned int total_rx_bytes; unsigned int total_rx_packets; int /*<<< orphan*/  (* alloc_rx_buf ) (struct e1000_ring*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  rx_hdr_split; struct pci_dev* pdev; struct net_device* netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int E1000_RXDEXT_ERR_FRAME_ERR_MASK ; 
 int /*<<< orphan*/  E1000_RXDPS_HDRSTAT_HDRSP ; 
 int E1000_RXD_STAT_DD ; 
 int E1000_RXD_STAT_EOP ; 
 int E1000_RX_BUFFER_WRITE ; 
 union e1000_rx_desc_packet_split* E1000_RX_DESC_PS (struct e1000_ring,unsigned int) ; 
 int FLAG2_CRC_STRIPPING ; 
 int FLAG2_IS_DISCARDING ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETIF_F_RXALL ; 
 int NETIF_F_RXFCS ; 
 union e1000_rx_desc_packet_split* NET_IP_ALIGN ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned int PS_PAGE_BUFFERS ; 
 int copybreak ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int e1000_desc_unused (struct e1000_ring*) ; 
 int /*<<< orphan*/  e1000_receive_skb (struct e1000_adapter*,struct net_device*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_rx_checksum (struct e1000_adapter*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  e1000_rx_hash (struct net_device*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/ * kmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prefetch (union e1000_rx_desc_packet_split*) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_ring*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct e1000_ring*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool e1000_clean_rx_irq_ps(struct e1000_ring *rx_ring, int *work_done,
				  int work_to_do)
{
	struct e1000_adapter *adapter = rx_ring->adapter;
	struct e1000_hw *hw = &adapter->hw;
	union e1000_rx_desc_packet_split *rx_desc, *next_rxd;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_buffer *buffer_info, *next_buffer;
	struct e1000_ps_page *ps_page;
	struct sk_buff *skb;
	unsigned int i, j;
	u32 length, staterr;
	int cleaned_count = 0;
	bool cleaned = false;
	unsigned int total_rx_bytes = 0, total_rx_packets = 0;

	i = rx_ring->next_to_clean;
	rx_desc = E1000_RX_DESC_PS(*rx_ring, i);
	staterr = le32_to_cpu(rx_desc->wb.middle.status_error);
	buffer_info = &rx_ring->buffer_info[i];

	while (staterr & E1000_RXD_STAT_DD) {
		if (*work_done >= work_to_do)
			break;
		(*work_done)++;
		skb = buffer_info->skb;
		dma_rmb();	/* read descriptor and rx_buffer_info after status DD */

		/* in the packet split case this is header only */
		prefetch(skb->data - NET_IP_ALIGN);

		i++;
		if (i == rx_ring->count)
			i = 0;
		next_rxd = E1000_RX_DESC_PS(*rx_ring, i);
		prefetch(next_rxd);

		next_buffer = &rx_ring->buffer_info[i];

		cleaned = true;
		cleaned_count++;
		dma_unmap_single(&pdev->dev, buffer_info->dma,
				 adapter->rx_ps_bsize0, DMA_FROM_DEVICE);
		buffer_info->dma = 0;

		/* see !EOP comment in other Rx routine */
		if (!(staterr & E1000_RXD_STAT_EOP))
			adapter->flags2 |= FLAG2_IS_DISCARDING;

		if (adapter->flags2 & FLAG2_IS_DISCARDING) {
			e_dbg("Packet Split buffers didn't pick up the full packet\n");
			dev_kfree_skb_irq(skb);
			if (staterr & E1000_RXD_STAT_EOP)
				adapter->flags2 &= ~FLAG2_IS_DISCARDING;
			goto next_desc;
		}

		if (unlikely((staterr & E1000_RXDEXT_ERR_FRAME_ERR_MASK) &&
			     !(netdev->features & NETIF_F_RXALL))) {
			dev_kfree_skb_irq(skb);
			goto next_desc;
		}

		length = le16_to_cpu(rx_desc->wb.middle.length0);

		if (!length) {
			e_dbg("Last part of the packet spanning multiple descriptors\n");
			dev_kfree_skb_irq(skb);
			goto next_desc;
		}

		/* Good Receive */
		skb_put(skb, length);

		{
			/* this looks ugly, but it seems compiler issues make
			 * it more efficient than reusing j
			 */
			int l1 = le16_to_cpu(rx_desc->wb.upper.length[0]);

			/* page alloc/put takes too long and effects small
			 * packet throughput, so unsplit small packets and
			 * save the alloc/put only valid in softirq (napi)
			 * context to call kmap_*
			 */
			if (l1 && (l1 <= copybreak) &&
			    ((length + l1) <= adapter->rx_ps_bsize0)) {
				u8 *vaddr;

				ps_page = &buffer_info->ps_pages[0];

				/* there is no documentation about how to call
				 * kmap_atomic, so we can't hold the mapping
				 * very long
				 */
				dma_sync_single_for_cpu(&pdev->dev,
							ps_page->dma,
							PAGE_SIZE,
							DMA_FROM_DEVICE);
				vaddr = kmap_atomic(ps_page->page);
				memcpy(skb_tail_pointer(skb), vaddr, l1);
				kunmap_atomic(vaddr);
				dma_sync_single_for_device(&pdev->dev,
							   ps_page->dma,
							   PAGE_SIZE,
							   DMA_FROM_DEVICE);

				/* remove the CRC */
				if (!(adapter->flags2 & FLAG2_CRC_STRIPPING)) {
					if (!(netdev->features & NETIF_F_RXFCS))
						l1 -= 4;
				}

				skb_put(skb, l1);
				goto copydone;
			}	/* if */
		}

		for (j = 0; j < PS_PAGE_BUFFERS; j++) {
			length = le16_to_cpu(rx_desc->wb.upper.length[j]);
			if (!length)
				break;

			ps_page = &buffer_info->ps_pages[j];
			dma_unmap_page(&pdev->dev, ps_page->dma, PAGE_SIZE,
				       DMA_FROM_DEVICE);
			ps_page->dma = 0;
			skb_fill_page_desc(skb, j, ps_page->page, 0, length);
			ps_page->page = NULL;
			skb->len += length;
			skb->data_len += length;
			skb->truesize += PAGE_SIZE;
		}

		/* strip the ethernet crc, problem is we're using pages now so
		 * this whole operation can get a little cpu intensive
		 */
		if (!(adapter->flags2 & FLAG2_CRC_STRIPPING)) {
			if (!(netdev->features & NETIF_F_RXFCS))
				pskb_trim(skb, skb->len - 4);
		}

copydone:
		total_rx_bytes += skb->len;
		total_rx_packets++;

		e1000_rx_checksum(adapter, staterr, skb);

		e1000_rx_hash(netdev, rx_desc->wb.lower.hi_dword.rss, skb);

		if (rx_desc->wb.upper.header_status &
		    cpu_to_le16(E1000_RXDPS_HDRSTAT_HDRSP))
			adapter->rx_hdr_split++;

		e1000_receive_skb(adapter, netdev, skb, staterr,
				  rx_desc->wb.middle.vlan);

next_desc:
		rx_desc->wb.middle.status_error &= cpu_to_le32(~0xFF);
		buffer_info->skb = NULL;

		/* return some buffers to hardware, one at a time is too slow */
		if (cleaned_count >= E1000_RX_BUFFER_WRITE) {
			adapter->alloc_rx_buf(rx_ring, cleaned_count,
					      GFP_ATOMIC);
			cleaned_count = 0;
		}

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;

		staterr = le32_to_cpu(rx_desc->wb.middle.status_error);
	}
	rx_ring->next_to_clean = i;

	cleaned_count = e1000_desc_unused(rx_ring);
	if (cleaned_count)
		adapter->alloc_rx_buf(rx_ring, cleaned_count, GFP_ATOMIC);

	adapter->total_rx_bytes += total_rx_bytes;
	adapter->total_rx_packets += total_rx_packets;
	return cleaned;
}