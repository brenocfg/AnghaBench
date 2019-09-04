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
typedef  scalar_t__ u32 ;
struct skb_frag_struct {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nfp_net_tx_ring {scalar_t__ wr_p; scalar_t__ rd_p; scalar_t__ qcp_rd_p; scalar_t__ cnt; int /*<<< orphan*/  idx; TYPE_2__* txbufs; int /*<<< orphan*/  qcp_q; struct nfp_net_r_vector* r_vec; } ;
struct nfp_net_r_vector {int /*<<< orphan*/  tx_sync; int /*<<< orphan*/  tx_pkts; int /*<<< orphan*/  tx_bytes; TYPE_1__* nfp_net; } ;
struct nfp_net_dp {int /*<<< orphan*/  netdev; int /*<<< orphan*/  dev; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_6__ {int nr_frags; struct skb_frag_struct* frags; } ;
struct TYPE_5__ {int fidx; scalar_t__ pkt_cnt; scalar_t__ real_len; struct sk_buff* skb; scalar_t__ dma_addr; } ;
struct TYPE_4__ {struct nfp_net_dp dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int D_IDX (struct nfp_net_tx_ring*,scalar_t__) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_consume_skb (struct sk_buff*,int) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (struct netdev_queue*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 scalar_t__ nfp_net_tx_ring_should_wake (struct nfp_net_tx_ring*) ; 
 scalar_t__ nfp_qcp_rd_ptr_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (struct skb_frag_struct const*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_tx_complete(struct nfp_net_tx_ring *tx_ring, int budget)
{
	struct nfp_net_r_vector *r_vec = tx_ring->r_vec;
	struct nfp_net_dp *dp = &r_vec->nfp_net->dp;
	const struct skb_frag_struct *frag;
	struct netdev_queue *nd_q;
	u32 done_pkts = 0, done_bytes = 0;
	struct sk_buff *skb;
	int todo, nr_frags;
	u32 qcp_rd_p;
	int fidx;
	int idx;

	if (tx_ring->wr_p == tx_ring->rd_p)
		return;

	/* Work out how many descriptors have been transmitted */
	qcp_rd_p = nfp_qcp_rd_ptr_read(tx_ring->qcp_q);

	if (qcp_rd_p == tx_ring->qcp_rd_p)
		return;

	todo = D_IDX(tx_ring, qcp_rd_p - tx_ring->qcp_rd_p);

	while (todo--) {
		idx = D_IDX(tx_ring, tx_ring->rd_p++);

		skb = tx_ring->txbufs[idx].skb;
		if (!skb)
			continue;

		nr_frags = skb_shinfo(skb)->nr_frags;
		fidx = tx_ring->txbufs[idx].fidx;

		if (fidx == -1) {
			/* unmap head */
			dma_unmap_single(dp->dev, tx_ring->txbufs[idx].dma_addr,
					 skb_headlen(skb), DMA_TO_DEVICE);

			done_pkts += tx_ring->txbufs[idx].pkt_cnt;
			done_bytes += tx_ring->txbufs[idx].real_len;
		} else {
			/* unmap fragment */
			frag = &skb_shinfo(skb)->frags[fidx];
			dma_unmap_page(dp->dev, tx_ring->txbufs[idx].dma_addr,
				       skb_frag_size(frag), DMA_TO_DEVICE);
		}

		/* check for last gather fragment */
		if (fidx == nr_frags - 1)
			napi_consume_skb(skb, budget);

		tx_ring->txbufs[idx].dma_addr = 0;
		tx_ring->txbufs[idx].skb = NULL;
		tx_ring->txbufs[idx].fidx = -2;
	}

	tx_ring->qcp_rd_p = qcp_rd_p;

	u64_stats_update_begin(&r_vec->tx_sync);
	r_vec->tx_bytes += done_bytes;
	r_vec->tx_pkts += done_pkts;
	u64_stats_update_end(&r_vec->tx_sync);

	if (!dp->netdev)
		return;

	nd_q = netdev_get_tx_queue(dp->netdev, tx_ring->idx);
	netdev_tx_completed_queue(nd_q, done_pkts, done_bytes);
	if (nfp_net_tx_ring_should_wake(tx_ring)) {
		/* Make sure TX thread will see updated tx_ring->rd_p */
		smp_mb();

		if (unlikely(netif_tx_queue_stopped(nd_q)))
			netif_tx_wake_queue(nd_q);
	}

	WARN_ONCE(tx_ring->wr_p - tx_ring->rd_p > tx_ring->cnt,
		  "TX ring corruption rd_p=%u wr_p=%u cnt=%u\n",
		  tx_ring->rd_p, tx_ring->wr_p, tx_ring->cnt);
}