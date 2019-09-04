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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct ixgb_rx_desc {scalar_t__ status; int /*<<< orphan*/  buff_addr; } ;
struct ixgb_desc_ring {unsigned int next_to_use; unsigned int count; struct ixgb_buffer* buffer_info; } ;
struct ixgb_buffer {int /*<<< orphan*/  dma; int /*<<< orphan*/  length; struct sk_buff* skb; } ;
struct ixgb_adapter {int /*<<< orphan*/  hw; int /*<<< orphan*/  alloc_rx_buff_failed; int /*<<< orphan*/  rx_buffer_len; struct pci_dev* pdev; struct net_device* netdev; struct ixgb_desc_ring rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 long IXGB_DESC_UNUSED (struct ixgb_desc_ring*) ; 
 struct ixgb_rx_desc* IXGB_RX_DESC (struct ixgb_desc_ring,unsigned int) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  RDT ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
ixgb_alloc_rx_buffers(struct ixgb_adapter *adapter, int cleaned_count)
{
	struct ixgb_desc_ring *rx_ring = &adapter->rx_ring;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct ixgb_rx_desc *rx_desc;
	struct ixgb_buffer *buffer_info;
	struct sk_buff *skb;
	unsigned int i;
	long cleancount;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];
	cleancount = IXGB_DESC_UNUSED(rx_ring);


	/* leave three descriptors unused */
	while (--cleancount > 2 && cleaned_count--) {
		/* recycle! its good for you */
		skb = buffer_info->skb;
		if (skb) {
			skb_trim(skb, 0);
			goto map_skb;
		}

		skb = netdev_alloc_skb_ip_align(netdev, adapter->rx_buffer_len);
		if (unlikely(!skb)) {
			/* Better luck next round */
			adapter->alloc_rx_buff_failed++;
			break;
		}

		buffer_info->skb = skb;
		buffer_info->length = adapter->rx_buffer_len;
map_skb:
		buffer_info->dma = dma_map_single(&pdev->dev,
		                                  skb->data,
		                                  adapter->rx_buffer_len,
						  DMA_FROM_DEVICE);
		if (dma_mapping_error(&pdev->dev, buffer_info->dma)) {
			adapter->alloc_rx_buff_failed++;
			break;
		}

		rx_desc = IXGB_RX_DESC(*rx_ring, i);
		rx_desc->buff_addr = cpu_to_le64(buffer_info->dma);
		/* guarantee DD bit not set now before h/w gets descriptor
		 * this is the rest of the workaround for h/w double
		 * writeback. */
		rx_desc->status = 0;


		if (++i == rx_ring->count)
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	}

	if (likely(rx_ring->next_to_use != i)) {
		rx_ring->next_to_use = i;
		if (unlikely(i-- == 0))
			i = (rx_ring->count - 1);

		/* Force memory writes to complete before letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable for weak-ordered memory model archs, such
		 * as IA-64). */
		wmb();
		IXGB_WRITE_REG(&adapter->hw, RDT, i);
	}
}