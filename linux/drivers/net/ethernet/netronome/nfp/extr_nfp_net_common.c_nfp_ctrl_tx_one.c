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
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; } ;
struct nfp_net_tx_ring {int /*<<< orphan*/  wr_ptr_add; int /*<<< orphan*/  wr_p; struct nfp_net_tx_desc* txds; struct nfp_net_tx_buf* txbufs; } ;
struct nfp_net_tx_desc {unsigned int offset_eop; scalar_t__ lso_hdrlen; scalar_t__ mss; scalar_t__ flags; void* data_len; void* dma_len; } ;
struct nfp_net_tx_buf {int fidx; int pkt_cnt; unsigned int real_len; int /*<<< orphan*/  dma_addr; struct sk_buff* skb; } ;
struct nfp_net_r_vector {int /*<<< orphan*/  tx_sync; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  queue; int /*<<< orphan*/  tx_busy; struct nfp_net_tx_ring* tx_ring; TYPE_1__* nfp_net; } ;
struct nfp_net_dp {int /*<<< orphan*/  dev; } ;
struct nfp_net {int /*<<< orphan*/  app; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  nr_frags; } ;
struct TYPE_3__ {struct nfp_net_dp dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int D_IDX (struct nfp_net_tx_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_META_PORT_ID_CTRL ; 
 int /*<<< orphan*/  NFP_NET_META_PORTID ; 
 unsigned int PCIE_DESC_TX_EOP ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfp_app_ctrl_has_meta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_desc_set_dma_addr (struct nfp_net_tx_desc*,int /*<<< orphan*/ ) ; 
 int nfp_net_tx_full (struct nfp_net_tx_ring*,int) ; 
 int /*<<< orphan*/  nfp_net_tx_xmit_more_flush (struct nfp_net_tx_ring*) ; 
 int /*<<< orphan*/  nn_dp_warn (struct nfp_net_dp*,char*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
nfp_ctrl_tx_one(struct nfp_net *nn, struct nfp_net_r_vector *r_vec,
		struct sk_buff *skb, bool old)
{
	unsigned int real_len = skb->len, meta_len = 0;
	struct nfp_net_tx_ring *tx_ring;
	struct nfp_net_tx_buf *txbuf;
	struct nfp_net_tx_desc *txd;
	struct nfp_net_dp *dp;
	dma_addr_t dma_addr;
	int wr_idx;

	dp = &r_vec->nfp_net->dp;
	tx_ring = r_vec->tx_ring;

	if (WARN_ON_ONCE(skb_shinfo(skb)->nr_frags)) {
		nn_dp_warn(dp, "Driver's CTRL TX does not implement gather\n");
		goto err_free;
	}

	if (unlikely(nfp_net_tx_full(tx_ring, 1))) {
		u64_stats_update_begin(&r_vec->tx_sync);
		r_vec->tx_busy++;
		u64_stats_update_end(&r_vec->tx_sync);
		if (!old)
			__skb_queue_tail(&r_vec->queue, skb);
		else
			__skb_queue_head(&r_vec->queue, skb);
		return true;
	}

	if (nfp_app_ctrl_has_meta(nn->app)) {
		if (unlikely(skb_headroom(skb) < 8)) {
			nn_dp_warn(dp, "CTRL TX on skb without headroom\n");
			goto err_free;
		}
		meta_len = 8;
		put_unaligned_be32(NFP_META_PORT_ID_CTRL, skb_push(skb, 4));
		put_unaligned_be32(NFP_NET_META_PORTID, skb_push(skb, 4));
	}

	/* Start with the head skbuf */
	dma_addr = dma_map_single(dp->dev, skb->data, skb_headlen(skb),
				  DMA_TO_DEVICE);
	if (dma_mapping_error(dp->dev, dma_addr))
		goto err_dma_warn;

	wr_idx = D_IDX(tx_ring, tx_ring->wr_p);

	/* Stash the soft descriptor of the head then initialize it */
	txbuf = &tx_ring->txbufs[wr_idx];
	txbuf->skb = skb;
	txbuf->dma_addr = dma_addr;
	txbuf->fidx = -1;
	txbuf->pkt_cnt = 1;
	txbuf->real_len = real_len;

	/* Build TX descriptor */
	txd = &tx_ring->txds[wr_idx];
	txd->offset_eop = meta_len | PCIE_DESC_TX_EOP;
	txd->dma_len = cpu_to_le16(skb_headlen(skb));
	nfp_desc_set_dma_addr(txd, dma_addr);
	txd->data_len = cpu_to_le16(skb->len);

	txd->flags = 0;
	txd->mss = 0;
	txd->lso_hdrlen = 0;

	tx_ring->wr_p++;
	tx_ring->wr_ptr_add++;
	nfp_net_tx_xmit_more_flush(tx_ring);

	return false;

err_dma_warn:
	nn_dp_warn(dp, "Failed to DMA map TX CTRL buffer\n");
err_free:
	u64_stats_update_begin(&r_vec->tx_sync);
	r_vec->tx_errors++;
	u64_stats_update_end(&r_vec->tx_sync);
	dev_kfree_skb_any(skb);
	return false;
}