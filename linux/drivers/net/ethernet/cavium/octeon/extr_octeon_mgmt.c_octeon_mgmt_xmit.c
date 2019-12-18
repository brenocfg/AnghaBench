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
struct TYPE_5__ {int tstamp; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
union mgmt_port_ring_entry {scalar_t__ d64; TYPE_1__ s; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct octeon_mgmt {int tx_current_fill; size_t tx_next; scalar_t__ mix; int /*<<< orphan*/  tx_ring_handle; int /*<<< orphan*/  dev; TYPE_4__ tx_list; scalar_t__* tx_ring; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_7__ {int tx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ MIX_ORING2 ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int OCTEON_MGMT_TX_RING_SIZE ; 
 int SKBTX_HW_TSTAMP ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_4__*,struct sk_buff*) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,int) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  octeon_mgmt_update_tx_stats (struct net_device*) ; 
 int ring_max_fill (int) ; 
 int /*<<< orphan*/  ring_size_to_bytes (int) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t
octeon_mgmt_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	struct octeon_mgmt *p = netdev_priv(netdev);
	union mgmt_port_ring_entry re;
	unsigned long flags;
	netdev_tx_t rv = NETDEV_TX_BUSY;

	re.d64 = 0;
	re.s.tstamp = ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) != 0);
	re.s.len = skb->len;
	re.s.addr = dma_map_single(p->dev, skb->data,
				   skb->len,
				   DMA_TO_DEVICE);

	spin_lock_irqsave(&p->tx_list.lock, flags);

	if (unlikely(p->tx_current_fill >= ring_max_fill(OCTEON_MGMT_TX_RING_SIZE) - 1)) {
		spin_unlock_irqrestore(&p->tx_list.lock, flags);
		netif_stop_queue(netdev);
		spin_lock_irqsave(&p->tx_list.lock, flags);
	}

	if (unlikely(p->tx_current_fill >=
		     ring_max_fill(OCTEON_MGMT_TX_RING_SIZE))) {
		spin_unlock_irqrestore(&p->tx_list.lock, flags);
		dma_unmap_single(p->dev, re.s.addr, re.s.len,
				 DMA_TO_DEVICE);
		goto out;
	}

	__skb_queue_tail(&p->tx_list, skb);

	/* Put it in the ring.  */
	p->tx_ring[p->tx_next] = re.d64;
	p->tx_next = (p->tx_next + 1) % OCTEON_MGMT_TX_RING_SIZE;
	p->tx_current_fill++;

	spin_unlock_irqrestore(&p->tx_list.lock, flags);

	dma_sync_single_for_device(p->dev, p->tx_ring_handle,
				   ring_size_to_bytes(OCTEON_MGMT_TX_RING_SIZE),
				   DMA_BIDIRECTIONAL);

	netdev->stats.tx_packets++;
	netdev->stats.tx_bytes += skb->len;

	/* Ring the bell.  */
	cvmx_write_csr(p->mix + MIX_ORING2, 1);

	netif_trans_update(netdev);
	rv = NETDEV_TX_OK;
out:
	octeon_mgmt_update_tx_stats(netdev);
	return rv;
}