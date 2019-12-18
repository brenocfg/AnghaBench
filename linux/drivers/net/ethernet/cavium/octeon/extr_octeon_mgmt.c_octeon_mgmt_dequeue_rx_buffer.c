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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
union mgmt_port_ring_entry {int /*<<< orphan*/  d64; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct octeon_mgmt {size_t rx_next; int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_list; int /*<<< orphan*/  rx_current_fill; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  rx_ring_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ ETH_FRAME_LEN ; 
 scalar_t__ OCTEON_MGMT_RX_HEADROOM ; 
 int OCTEON_MGMT_RX_RING_SIZE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_size_to_bytes (int) ; 

__attribute__((used)) static u64 octeon_mgmt_dequeue_rx_buffer(struct octeon_mgmt *p,
					 struct sk_buff **pskb)
{
	union mgmt_port_ring_entry re;

	dma_sync_single_for_cpu(p->dev, p->rx_ring_handle,
				ring_size_to_bytes(OCTEON_MGMT_RX_RING_SIZE),
				DMA_BIDIRECTIONAL);

	re.d64 = p->rx_ring[p->rx_next];
	p->rx_next = (p->rx_next + 1) % OCTEON_MGMT_RX_RING_SIZE;
	p->rx_current_fill--;
	*pskb = __skb_dequeue(&p->rx_list);

	dma_unmap_single(p->dev, re.s.addr,
			 ETH_FRAME_LEN + OCTEON_MGMT_RX_HEADROOM,
			 DMA_FROM_DEVICE);

	return re.d64;
}