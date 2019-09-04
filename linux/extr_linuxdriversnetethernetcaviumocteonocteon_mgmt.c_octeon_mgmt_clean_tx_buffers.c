#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tstamp; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
union mgmt_port_ring_entry {TYPE_2__ s; int /*<<< orphan*/  d64; } ;
struct TYPE_4__ {int orcnt; } ;
union cvmx_mixx_orcnt {void* u64; TYPE_1__ s; } ;
typedef  void* u64 ;
typedef  int /*<<< orphan*/  ts ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct octeon_mgmt {size_t tx_next_clean; int /*<<< orphan*/  netdev; scalar_t__ mix; int /*<<< orphan*/  port; int /*<<< orphan*/  dev; TYPE_3__ tx_list; int /*<<< orphan*/  tx_current_fill; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  tx_ring_handle; } ;

/* Variables and functions */
 scalar_t__ CVMX_MIXX_TSCTL (int /*<<< orphan*/ ) ; 
 scalar_t__ CVMX_MIXX_TSTAMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ MIX_ORCNT ; 
 int OCTEON_MGMT_TX_RING_SIZE ; 
 struct sk_buff* __skb_dequeue (TYPE_3__*) ; 
 void* cvmx_read_csr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,void*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (void*) ; 
 int /*<<< orphan*/  ring_size_to_bytes (int) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_mgmt_clean_tx_buffers(struct octeon_mgmt *p)
{
	union cvmx_mixx_orcnt mix_orcnt;
	union mgmt_port_ring_entry re;
	struct sk_buff *skb;
	int cleaned = 0;
	unsigned long flags;

	mix_orcnt.u64 = cvmx_read_csr(p->mix + MIX_ORCNT);
	while (mix_orcnt.s.orcnt) {
		spin_lock_irqsave(&p->tx_list.lock, flags);

		mix_orcnt.u64 = cvmx_read_csr(p->mix + MIX_ORCNT);

		if (mix_orcnt.s.orcnt == 0) {
			spin_unlock_irqrestore(&p->tx_list.lock, flags);
			break;
		}

		dma_sync_single_for_cpu(p->dev, p->tx_ring_handle,
					ring_size_to_bytes(OCTEON_MGMT_TX_RING_SIZE),
					DMA_BIDIRECTIONAL);

		re.d64 = p->tx_ring[p->tx_next_clean];
		p->tx_next_clean =
			(p->tx_next_clean + 1) % OCTEON_MGMT_TX_RING_SIZE;
		skb = __skb_dequeue(&p->tx_list);

		mix_orcnt.u64 = 0;
		mix_orcnt.s.orcnt = 1;

		/* Acknowledge to hardware that we have the buffer.  */
		cvmx_write_csr(p->mix + MIX_ORCNT, mix_orcnt.u64);
		p->tx_current_fill--;

		spin_unlock_irqrestore(&p->tx_list.lock, flags);

		dma_unmap_single(p->dev, re.s.addr, re.s.len,
				 DMA_TO_DEVICE);

		/* Read the hardware TX timestamp if one was recorded */
		if (unlikely(re.s.tstamp)) {
			struct skb_shared_hwtstamps ts;
			u64 ns;

			memset(&ts, 0, sizeof(ts));
			/* Read the timestamp */
			ns = cvmx_read_csr(CVMX_MIXX_TSTAMP(p->port));
			/* Remove the timestamp from the FIFO */
			cvmx_write_csr(CVMX_MIXX_TSCTL(p->port), 0);
			/* Tell the kernel about the timestamp */
			ts.hwtstamp = ns_to_ktime(ns);
			skb_tstamp_tx(skb, &ts);
		}

		dev_kfree_skb_any(skb);
		cleaned++;

		mix_orcnt.u64 = cvmx_read_csr(p->mix + MIX_ORCNT);
	}

	if (cleaned && netif_queue_stopped(p->netdev))
		netif_wake_queue(p->netdev);
}