#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  buffer_addr; } ;
union e1000_rx_desc_extended {TYPE_1__ read; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct e1000_ring {unsigned int next_to_use; unsigned int count; struct e1000_buffer* buffer_info; int /*<<< orphan*/  tail; struct e1000_adapter* adapter; } ;
struct e1000_buffer {int /*<<< orphan*/  dma; struct sk_buff* skb; } ;
struct e1000_adapter {unsigned int rx_buffer_len; int flags2; int /*<<< orphan*/  rx_dma_failed; int /*<<< orphan*/  alloc_rx_buff_failed; struct pci_dev* pdev; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int E1000_RX_BUFFER_WRITE ; 
 union e1000_rx_desc_extended* E1000_RX_DESC_EXT (struct e1000_ring,unsigned int) ; 
 int FLAG2_PCIM2PCI_ARBITER_WA ; 
 struct sk_buff* __netdev_alloc_skb_ip_align (struct net_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_update_rdt_wa (struct e1000_ring*,unsigned int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_alloc_rx_buffers(struct e1000_ring *rx_ring,
				   int cleaned_count, gfp_t gfp)
{
	struct e1000_adapter *adapter = rx_ring->adapter;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	union e1000_rx_desc_extended *rx_desc;
	struct e1000_buffer *buffer_info;
	struct sk_buff *skb;
	unsigned int i;
	unsigned int bufsz = adapter->rx_buffer_len;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	while (cleaned_count--) {
		skb = buffer_info->skb;
		if (skb) {
			skb_trim(skb, 0);
			goto map_skb;
		}

		skb = __netdev_alloc_skb_ip_align(netdev, bufsz, gfp);
		if (!skb) {
			/* Better luck next round */
			adapter->alloc_rx_buff_failed++;
			break;
		}

		buffer_info->skb = skb;
map_skb:
		buffer_info->dma = dma_map_single(&pdev->dev, skb->data,
						  adapter->rx_buffer_len,
						  DMA_FROM_DEVICE);
		if (dma_mapping_error(&pdev->dev, buffer_info->dma)) {
			dev_err(&pdev->dev, "Rx DMA map failed\n");
			adapter->rx_dma_failed++;
			break;
		}

		rx_desc = E1000_RX_DESC_EXT(*rx_ring, i);
		rx_desc->read.buffer_addr = cpu_to_le64(buffer_info->dma);

		if (unlikely(!(i & (E1000_RX_BUFFER_WRITE - 1)))) {
			/* Force memory writes to complete before letting h/w
			 * know there are new descriptors to fetch.  (Only
			 * applicable for weak-ordered memory model archs,
			 * such as IA-64).
			 */
			wmb();
			if (adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
				e1000e_update_rdt_wa(rx_ring, i);
			else
				writel(i, rx_ring->tail);
		}
		i++;
		if (i == rx_ring->count)
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	}

	rx_ring->next_to_use = i;
}