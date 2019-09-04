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
struct TYPE_2__ {unsigned int len; int /*<<< orphan*/  addr; } ;
union mgmt_port_ring_entry {scalar_t__ d64; TYPE_1__ s; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct octeon_mgmt {scalar_t__ rx_current_fill; size_t rx_next_fill; scalar_t__ mix; int /*<<< orphan*/  rx_ring_handle; int /*<<< orphan*/  dev; scalar_t__* rx_ring; int /*<<< orphan*/  rx_list; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ MIX_IRING2 ; 
 int NET_IP_ALIGN ; 
 int OCTEON_MGMT_RX_HEADROOM ; 
 int OCTEON_MGMT_RX_RING_SIZE ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,int) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,unsigned int) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 
 scalar_t__ ring_max_fill (int) ; 
 int /*<<< orphan*/  ring_size_to_bytes (int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void octeon_mgmt_rx_fill_ring(struct net_device *netdev)
{
	struct octeon_mgmt *p = netdev_priv(netdev);

	while (p->rx_current_fill < ring_max_fill(OCTEON_MGMT_RX_RING_SIZE)) {
		unsigned int size;
		union mgmt_port_ring_entry re;
		struct sk_buff *skb;

		/* CN56XX pass 1 needs 8 bytes of padding.  */
		size = netdev->mtu + OCTEON_MGMT_RX_HEADROOM + 8 + NET_IP_ALIGN;

		skb = netdev_alloc_skb(netdev, size);
		if (!skb)
			break;
		skb_reserve(skb, NET_IP_ALIGN);
		__skb_queue_tail(&p->rx_list, skb);

		re.d64 = 0;
		re.s.len = size;
		re.s.addr = dma_map_single(p->dev, skb->data,
					   size,
					   DMA_FROM_DEVICE);

		/* Put it in the ring.  */
		p->rx_ring[p->rx_next_fill] = re.d64;
		dma_sync_single_for_device(p->dev, p->rx_ring_handle,
					   ring_size_to_bytes(OCTEON_MGMT_RX_RING_SIZE),
					   DMA_BIDIRECTIONAL);
		p->rx_next_fill =
			(p->rx_next_fill + 1) % OCTEON_MGMT_RX_RING_SIZE;
		p->rx_current_fill++;
		/* Ring the bell.  */
		cvmx_write_csr(p->mix + MIX_IRING2, 1);
	}
}