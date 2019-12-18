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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u16 ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; } ;
struct nfp_net_tx_ring {int wr_p; size_t idx; int wr_ptr_add; struct nfp_net_tx_buf* txbufs; scalar_t__ cnt; struct nfp_net_tx_desc* txds; int /*<<< orphan*/  rd_p; struct nfp_net_r_vector* r_vec; } ;
struct nfp_net_tx_desc {int offset_eop; int /*<<< orphan*/ * vals8; void* dma_len; void* vlan; int /*<<< orphan*/  flags; scalar_t__ lso_hdrlen; scalar_t__ mss; void* data_len; } ;
struct nfp_net_tx_buf {int fidx; int pkt_cnt; unsigned int real_len; void* dma_addr; struct sk_buff* skb; } ;
struct nfp_net_r_vector {int /*<<< orphan*/  tx_sync; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_gather; int /*<<< orphan*/  tx_busy; } ;
struct nfp_net_dp {int ctrl; int /*<<< orphan*/  dev; int /*<<< orphan*/  netdev; struct nfp_net_tx_ring* tx_rings; } ;
struct nfp_net {struct nfp_net_dp dp; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  void* dma_addr_t ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int D_IDX (struct nfp_net_tx_ring*,int) ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int NFP_NET_CFG_CTRL_TXVLAN ; 
 int PCIE_DESC_TX_EOP ; 
 int /*<<< orphan*/  PCIE_DESC_TX_VLAN ; 
 scalar_t__ __netdev_tx_sent_queue (struct netdev_queue*,unsigned int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 void* dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,size_t) ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  nfp_desc_set_dma_addr (struct nfp_net_tx_desc*,void*) ; 
 int nfp_net_prep_tx_meta (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* nfp_net_tls_tx (struct nfp_net_dp*,struct nfp_net_r_vector*,struct sk_buff*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfp_net_tls_tx_undo (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_tx_csum (struct nfp_net_dp*,struct nfp_net_r_vector*,struct nfp_net_tx_buf*,struct nfp_net_tx_desc*,struct sk_buff*) ; 
 int nfp_net_tx_full (struct nfp_net_tx_ring*,int) ; 
 scalar_t__ nfp_net_tx_ring_should_stop (struct nfp_net_tx_ring*) ; 
 int /*<<< orphan*/  nfp_net_tx_ring_stop (struct netdev_queue*,struct nfp_net_tx_ring*) ; 
 int /*<<< orphan*/  nfp_net_tx_tso (struct nfp_net_r_vector*,struct nfp_net_tx_buf*,struct nfp_net_tx_desc*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  nfp_net_tx_xmit_more_flush (struct nfp_net_tx_ring*) ; 
 int /*<<< orphan*/  nn_dp_warn (struct nfp_net_dp*,char*,...) ; 
 void* skb_frag_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/  const*) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 unsigned int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nfp_net_tx(struct sk_buff *skb, struct net_device *netdev)
{
	struct nfp_net *nn = netdev_priv(netdev);
	const skb_frag_t *frag;
	int f, nr_frags, wr_idx, md_bytes;
	struct nfp_net_tx_ring *tx_ring;
	struct nfp_net_r_vector *r_vec;
	struct nfp_net_tx_buf *txbuf;
	struct nfp_net_tx_desc *txd;
	struct netdev_queue *nd_q;
	struct nfp_net_dp *dp;
	dma_addr_t dma_addr;
	unsigned int fsize;
	u64 tls_handle = 0;
	u16 qidx;

	dp = &nn->dp;
	qidx = skb_get_queue_mapping(skb);
	tx_ring = &dp->tx_rings[qidx];
	r_vec = tx_ring->r_vec;

	nr_frags = skb_shinfo(skb)->nr_frags;

	if (unlikely(nfp_net_tx_full(tx_ring, nr_frags + 1))) {
		nn_dp_warn(dp, "TX ring %d busy. wrp=%u rdp=%u\n",
			   qidx, tx_ring->wr_p, tx_ring->rd_p);
		nd_q = netdev_get_tx_queue(dp->netdev, qidx);
		netif_tx_stop_queue(nd_q);
		nfp_net_tx_xmit_more_flush(tx_ring);
		u64_stats_update_begin(&r_vec->tx_sync);
		r_vec->tx_busy++;
		u64_stats_update_end(&r_vec->tx_sync);
		return NETDEV_TX_BUSY;
	}

	skb = nfp_net_tls_tx(dp, r_vec, skb, &tls_handle, &nr_frags);
	if (unlikely(!skb)) {
		nfp_net_tx_xmit_more_flush(tx_ring);
		return NETDEV_TX_OK;
	}

	md_bytes = nfp_net_prep_tx_meta(skb, tls_handle);
	if (unlikely(md_bytes < 0))
		goto err_flush;

	/* Start with the head skbuf */
	dma_addr = dma_map_single(dp->dev, skb->data, skb_headlen(skb),
				  DMA_TO_DEVICE);
	if (dma_mapping_error(dp->dev, dma_addr))
		goto err_dma_err;

	wr_idx = D_IDX(tx_ring, tx_ring->wr_p);

	/* Stash the soft descriptor of the head then initialize it */
	txbuf = &tx_ring->txbufs[wr_idx];
	txbuf->skb = skb;
	txbuf->dma_addr = dma_addr;
	txbuf->fidx = -1;
	txbuf->pkt_cnt = 1;
	txbuf->real_len = skb->len;

	/* Build TX descriptor */
	txd = &tx_ring->txds[wr_idx];
	txd->offset_eop = (nr_frags ? 0 : PCIE_DESC_TX_EOP) | md_bytes;
	txd->dma_len = cpu_to_le16(skb_headlen(skb));
	nfp_desc_set_dma_addr(txd, dma_addr);
	txd->data_len = cpu_to_le16(skb->len);

	txd->flags = 0;
	txd->mss = 0;
	txd->lso_hdrlen = 0;

	/* Do not reorder - tso may adjust pkt cnt, vlan may override fields */
	nfp_net_tx_tso(r_vec, txbuf, txd, skb, md_bytes);
	nfp_net_tx_csum(dp, r_vec, txbuf, txd, skb);
	if (skb_vlan_tag_present(skb) && dp->ctrl & NFP_NET_CFG_CTRL_TXVLAN) {
		txd->flags |= PCIE_DESC_TX_VLAN;
		txd->vlan = cpu_to_le16(skb_vlan_tag_get(skb));
	}

	/* Gather DMA */
	if (nr_frags > 0) {
		__le64 second_half;

		/* all descs must match except for in addr, length and eop */
		second_half = txd->vals8[1];

		for (f = 0; f < nr_frags; f++) {
			frag = &skb_shinfo(skb)->frags[f];
			fsize = skb_frag_size(frag);

			dma_addr = skb_frag_dma_map(dp->dev, frag, 0,
						    fsize, DMA_TO_DEVICE);
			if (dma_mapping_error(dp->dev, dma_addr))
				goto err_unmap;

			wr_idx = D_IDX(tx_ring, wr_idx + 1);
			tx_ring->txbufs[wr_idx].skb = skb;
			tx_ring->txbufs[wr_idx].dma_addr = dma_addr;
			tx_ring->txbufs[wr_idx].fidx = f;

			txd = &tx_ring->txds[wr_idx];
			txd->dma_len = cpu_to_le16(fsize);
			nfp_desc_set_dma_addr(txd, dma_addr);
			txd->offset_eop = md_bytes |
				((f == nr_frags - 1) ? PCIE_DESC_TX_EOP : 0);
			txd->vals8[1] = second_half;
		}

		u64_stats_update_begin(&r_vec->tx_sync);
		r_vec->tx_gather++;
		u64_stats_update_end(&r_vec->tx_sync);
	}

	skb_tx_timestamp(skb);

	nd_q = netdev_get_tx_queue(dp->netdev, tx_ring->idx);

	tx_ring->wr_p += nr_frags + 1;
	if (nfp_net_tx_ring_should_stop(tx_ring))
		nfp_net_tx_ring_stop(nd_q, tx_ring);

	tx_ring->wr_ptr_add += nr_frags + 1;
	if (__netdev_tx_sent_queue(nd_q, txbuf->real_len, netdev_xmit_more()))
		nfp_net_tx_xmit_more_flush(tx_ring);

	return NETDEV_TX_OK;

err_unmap:
	while (--f >= 0) {
		frag = &skb_shinfo(skb)->frags[f];
		dma_unmap_page(dp->dev, tx_ring->txbufs[wr_idx].dma_addr,
			       skb_frag_size(frag), DMA_TO_DEVICE);
		tx_ring->txbufs[wr_idx].skb = NULL;
		tx_ring->txbufs[wr_idx].dma_addr = 0;
		tx_ring->txbufs[wr_idx].fidx = -2;
		wr_idx = wr_idx - 1;
		if (wr_idx < 0)
			wr_idx += tx_ring->cnt;
	}
	dma_unmap_single(dp->dev, tx_ring->txbufs[wr_idx].dma_addr,
			 skb_headlen(skb), DMA_TO_DEVICE);
	tx_ring->txbufs[wr_idx].skb = NULL;
	tx_ring->txbufs[wr_idx].dma_addr = 0;
	tx_ring->txbufs[wr_idx].fidx = -2;
err_dma_err:
	nn_dp_warn(dp, "Failed to map DMA TX buffer\n");
err_flush:
	nfp_net_tx_xmit_more_flush(tx_ring);
	u64_stats_update_begin(&r_vec->tx_sync);
	r_vec->tx_errors++;
	u64_stats_update_end(&r_vec->tx_sync);
	nfp_net_tls_tx_undo(skb, tls_handle);
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}