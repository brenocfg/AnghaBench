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
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct rx_free_desc {scalar_t__ coalese; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  buffer_addr; } ;
struct pci_dev {int dummy; } ;
struct page {int dummy; } ;
struct atl1_rfd_ring {size_t count; int /*<<< orphan*/  next_to_use; struct atl1_buffer* buffer_info; } ;
struct atl1_buffer {int alloced; size_t length; int /*<<< orphan*/  dma; struct sk_buff* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; } ;
struct atl1_adapter {scalar_t__ rx_buffer_len; TYPE_1__ soft_stats; int /*<<< orphan*/  netdev; struct pci_dev* pdev; struct atl1_rfd_ring rfd_ring; } ;

/* Variables and functions */
 struct rx_free_desc* ATL1_RFD_DESC (struct atl1_rfd_ring*,size_t) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long offset_in_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_page (struct pci_dev*,struct page*,unsigned long,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static u16 atl1_alloc_rx_buffers(struct atl1_adapter *adapter)
{
	struct atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	struct pci_dev *pdev = adapter->pdev;
	struct page *page;
	unsigned long offset;
	struct atl1_buffer *buffer_info, *next_info;
	struct sk_buff *skb;
	u16 num_alloc = 0;
	u16 rfd_next_to_use, next_next;
	struct rx_free_desc *rfd_desc;

	next_next = rfd_next_to_use = atomic_read(&rfd_ring->next_to_use);
	if (++next_next == rfd_ring->count)
		next_next = 0;
	buffer_info = &rfd_ring->buffer_info[rfd_next_to_use];
	next_info = &rfd_ring->buffer_info[next_next];

	while (!buffer_info->alloced && !next_info->alloced) {
		if (buffer_info->skb) {
			buffer_info->alloced = 1;
			goto next;
		}

		rfd_desc = ATL1_RFD_DESC(rfd_ring, rfd_next_to_use);

		skb = netdev_alloc_skb_ip_align(adapter->netdev,
						adapter->rx_buffer_len);
		if (unlikely(!skb)) {
			/* Better luck next round */
			adapter->soft_stats.rx_dropped++;
			break;
		}

		buffer_info->alloced = 1;
		buffer_info->skb = skb;
		buffer_info->length = (u16) adapter->rx_buffer_len;
		page = virt_to_page(skb->data);
		offset = offset_in_page(skb->data);
		buffer_info->dma = pci_map_page(pdev, page, offset,
						adapter->rx_buffer_len,
						PCI_DMA_FROMDEVICE);
		rfd_desc->buffer_addr = cpu_to_le64(buffer_info->dma);
		rfd_desc->buf_len = cpu_to_le16(adapter->rx_buffer_len);
		rfd_desc->coalese = 0;

next:
		rfd_next_to_use = next_next;
		if (unlikely(++next_next == rfd_ring->count))
			next_next = 0;

		buffer_info = &rfd_ring->buffer_info[rfd_next_to_use];
		next_info = &rfd_ring->buffer_info[next_next];
		num_alloc++;
	}

	if (num_alloc) {
		/*
		 * Force memory writes to complete before letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable for weak-ordered memory model archs,
		 * such as IA-64).
		 */
		wmb();
		atomic_set(&rfd_ring->next_to_use, (int)rfd_next_to_use);
	}
	return num_alloc;
}