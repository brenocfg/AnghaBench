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
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct nx_host_rds_ring {int /*<<< orphan*/  dma_size; struct netxen_rx_buffer* rx_buf_arr; } ;
struct netxen_rx_buffer {int /*<<< orphan*/  state; struct sk_buff* skb; int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  csummed; } ;
struct netxen_adapter {TYPE_2__ stats; TYPE_1__* netdev; int /*<<< orphan*/  pdev; } ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  NETXEN_BUFFER_FREE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 size_t STATUS_CKSUM_OK ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *netxen_process_rxbuf(struct netxen_adapter *adapter,
		struct nx_host_rds_ring *rds_ring, u16 index, u16 cksum)
{
	struct netxen_rx_buffer *buffer;
	struct sk_buff *skb;

	buffer = &rds_ring->rx_buf_arr[index];

	pci_unmap_single(adapter->pdev, buffer->dma, rds_ring->dma_size,
			PCI_DMA_FROMDEVICE);

	skb = buffer->skb;
	if (!skb)
		goto no_skb;

	if (likely((adapter->netdev->features & NETIF_F_RXCSUM)
	    && cksum == STATUS_CKSUM_OK)) {
		adapter->stats.csummed++;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	} else
		skb->ip_summed = CHECKSUM_NONE;

	buffer->skb = NULL;
no_skb:
	buffer->state = NETXEN_BUFFER_FREE;
	return skb;
}