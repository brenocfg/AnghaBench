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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; struct ixgb_rx_desc* data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct ixgb_rx_desc {int status; int errors; scalar_t__ special; scalar_t__ length; scalar_t__ dma; struct sk_buff* skb; } ;
struct ixgb_desc_ring {unsigned int next_to_clean; unsigned int count; struct ixgb_rx_desc* buffer_info; } ;
struct ixgb_buffer {int status; int errors; scalar_t__ special; scalar_t__ length; scalar_t__ dma; struct sk_buff* skb; } ;
struct ixgb_adapter {int /*<<< orphan*/  napi; struct pci_dev* pdev; struct net_device* netdev; struct ixgb_desc_ring rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int IXGB_DESC_UNUSED (struct ixgb_desc_ring*) ; 
 int IXGB_RX_BUFFER_WRITE ; 
 struct ixgb_rx_desc* IXGB_RX_DESC (struct ixgb_desc_ring,unsigned int) ; 
 int IXGB_RX_DESC_ERRORS_CE ; 
 int IXGB_RX_DESC_ERRORS_P ; 
 int IXGB_RX_DESC_ERRORS_RXE ; 
 int IXGB_RX_DESC_ERRORS_SE ; 
 int IXGB_RX_DESC_STATUS_DD ; 
 int IXGB_RX_DESC_STATUS_EOP ; 
 int IXGB_RX_DESC_STATUS_VP ; 
 struct ixgb_rx_desc* NET_IP_ALIGN ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgb_alloc_rx_buffers (struct ixgb_adapter*,int) ; 
 int /*<<< orphan*/  ixgb_check_copybreak (int /*<<< orphan*/ *,struct ixgb_rx_desc*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int /*<<< orphan*/  ixgb_rx_checksum (struct ixgb_adapter*,struct ixgb_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (struct ixgb_rx_desc*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
ixgb_clean_rx_irq(struct ixgb_adapter *adapter, int *work_done, int work_to_do)
{
	struct ixgb_desc_ring *rx_ring = &adapter->rx_ring;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct ixgb_rx_desc *rx_desc, *next_rxd;
	struct ixgb_buffer *buffer_info, *next_buffer, *next2_buffer;
	u32 length;
	unsigned int i, j;
	int cleaned_count = 0;
	bool cleaned = false;

	i = rx_ring->next_to_clean;
	rx_desc = IXGB_RX_DESC(*rx_ring, i);
	buffer_info = &rx_ring->buffer_info[i];

	while (rx_desc->status & IXGB_RX_DESC_STATUS_DD) {
		struct sk_buff *skb;
		u8 status;

		if (*work_done >= work_to_do)
			break;

		(*work_done)++;
		rmb();	/* read descriptor and rx_buffer_info after status DD */
		status = rx_desc->status;
		skb = buffer_info->skb;
		buffer_info->skb = NULL;

		prefetch(skb->data - NET_IP_ALIGN);

		if (++i == rx_ring->count)
			i = 0;
		next_rxd = IXGB_RX_DESC(*rx_ring, i);
		prefetch(next_rxd);

		j = i + 1;
		if (j == rx_ring->count)
			j = 0;
		next2_buffer = &rx_ring->buffer_info[j];
		prefetch(next2_buffer);

		next_buffer = &rx_ring->buffer_info[i];

		cleaned = true;
		cleaned_count++;

		dma_unmap_single(&pdev->dev,
				 buffer_info->dma,
				 buffer_info->length,
				 DMA_FROM_DEVICE);
		buffer_info->dma = 0;

		length = le16_to_cpu(rx_desc->length);
		rx_desc->length = 0;

		if (unlikely(!(status & IXGB_RX_DESC_STATUS_EOP))) {

			/* All receives must fit into a single buffer */

			pr_debug("Receive packet consumed multiple buffers length<%x>\n",
				 length);

			dev_kfree_skb_irq(skb);
			goto rxdesc_done;
		}

		if (unlikely(rx_desc->errors &
		    (IXGB_RX_DESC_ERRORS_CE | IXGB_RX_DESC_ERRORS_SE |
		     IXGB_RX_DESC_ERRORS_P | IXGB_RX_DESC_ERRORS_RXE))) {
			dev_kfree_skb_irq(skb);
			goto rxdesc_done;
		}

		ixgb_check_copybreak(&adapter->napi, buffer_info, length, &skb);

		/* Good Receive */
		skb_put(skb, length);

		/* Receive Checksum Offload */
		ixgb_rx_checksum(adapter, rx_desc, skb);

		skb->protocol = eth_type_trans(skb, netdev);
		if (status & IXGB_RX_DESC_STATUS_VP)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       le16_to_cpu(rx_desc->special));

		netif_receive_skb(skb);

rxdesc_done:
		/* clean up descriptor, might be written over by hw */
		rx_desc->status = 0;

		/* return some buffers to hardware, one at a time is too slow */
		if (unlikely(cleaned_count >= IXGB_RX_BUFFER_WRITE)) {
			ixgb_alloc_rx_buffers(adapter, cleaned_count);
			cleaned_count = 0;
		}

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;
	}

	rx_ring->next_to_clean = i;

	cleaned_count = IXGB_DESC_UNUSED(rx_ring);
	if (cleaned_count)
		ixgb_alloc_rx_buffers(adapter, cleaned_count);

	return cleaned;
}