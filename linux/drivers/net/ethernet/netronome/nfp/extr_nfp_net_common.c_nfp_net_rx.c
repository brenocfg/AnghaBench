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
typedef  int u32 ;
struct xdp_buff {void* data_hard_start; void* data; void* data_meta; void* data_end; int /*<<< orphan*/ * rxq; } ;
struct sk_buff {int decrypted; struct net_device* dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  mark; } ;
struct nfp_net_tx_ring {scalar_t__ wr_p; scalar_t__ rd_p; scalar_t__ wr_ptr_add; } ;
struct nfp_net_rx_ring {struct nfp_net_r_vector* r_vec; int /*<<< orphan*/  idx; struct nfp_net_rx_buf* rxbufs; int /*<<< orphan*/  rd_p; struct nfp_net_rx_desc* rxds; int /*<<< orphan*/  xdp_rxq; } ;
struct TYPE_4__ {int meta_len_dd; int flags; int /*<<< orphan*/  vlan; int /*<<< orphan*/  data_len; } ;
struct nfp_net_rx_desc {TYPE_2__ rxd; } ;
struct nfp_net_rx_buf {void* frag; scalar_t__ dma_addr; } ;
struct nfp_net_r_vector {unsigned int rx_bytes; int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_sync; int /*<<< orphan*/  hw_tls_rx; int /*<<< orphan*/  rx_pkts; struct nfp_net_tx_ring* xdp_ring; TYPE_1__* nfp_net; } ;
struct nfp_net_dp {unsigned int fl_bufsz; int rx_dma_off; unsigned int rx_offset; struct net_device* netdev; int /*<<< orphan*/  chained_metadata_format; int /*<<< orphan*/  xdp_prog; } ;
struct nfp_net {int /*<<< orphan*/  app; } ;
struct nfp_meta_parsed {scalar_t__ portid; int /*<<< orphan*/  hash_type; int /*<<< orphan*/  hash; int /*<<< orphan*/  mark; } ;
struct net_device {int dummy; } ;
struct bpf_prog {int dummy; } ;
typedef  int /*<<< orphan*/  meta ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_3__ {struct nfp_net_dp dp; } ;

/* Variables and functions */
 int D_IDX (struct nfp_net_rx_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ NFP_META_PORT_ID_CTRL ; 
 unsigned int NFP_NET_CFG_RX_OFFSET_DYNAMIC ; 
 unsigned int NFP_NET_MAX_PREPEND ; 
 int NFP_NET_RX_BUF_HEADROOM ; 
 unsigned int PAGE_SIZE ; 
 int PCIE_DESC_RX_DD ; 
 int PCIE_DESC_RX_DECRYPTED ; 
 unsigned int PCIE_DESC_RX_META_LEN_MASK ; 
 int PCIE_DESC_RX_VLAN ; 
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
#define  XDP_ABORTED 131 
#define  XDP_DROP 130 
#define  XDP_PASS 129 
#define  XDP_TX 128 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 int bpf_prog_run_xdp (struct bpf_prog*,struct xdp_buff*) ; 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 struct sk_buff* build_skb (void*,unsigned int) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct nfp_meta_parsed*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_app_ctrl_rx_raw (int /*<<< orphan*/ ,void*,unsigned int) ; 
 struct net_device* nfp_app_dev_get (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  nfp_net_dma_sync_cpu_rx (struct nfp_net_dp*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  nfp_net_dma_unmap_rx (struct nfp_net_dp*,scalar_t__) ; 
 void* nfp_net_napi_alloc_one (struct nfp_net_dp*,scalar_t__*) ; 
 void* nfp_net_parse_meta (struct net_device*,struct nfp_meta_parsed*,void*,unsigned int) ; 
 int /*<<< orphan*/  nfp_net_rx_csum (struct nfp_net_dp*,struct nfp_net_r_vector*,struct nfp_net_rx_desc*,struct nfp_meta_parsed*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_net_rx_drop (struct nfp_net_dp*,struct nfp_net_r_vector*,struct nfp_net_rx_ring*,struct nfp_net_rx_buf*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_net_rx_give_one (struct nfp_net_dp*,struct nfp_net_rx_ring*,void*,scalar_t__) ; 
 int /*<<< orphan*/  nfp_net_set_hash_desc (struct net_device*,struct nfp_meta_parsed*,void*,struct nfp_net_rx_desc*) ; 
 int /*<<< orphan*/  nfp_net_tx_xdp_buf (struct nfp_net_dp*,struct nfp_net_rx_ring*,struct nfp_net_tx_ring*,struct nfp_net_rx_buf*,unsigned int,unsigned int,int*) ; 
 int /*<<< orphan*/  nfp_net_tx_xmit_more_flush (struct nfp_net_tx_ring*) ; 
 int /*<<< orphan*/  nfp_net_xdp_complete (struct nfp_net_tx_ring*) ; 
 scalar_t__ nfp_netdev_is_nfp_repr (struct net_device*) ; 
 int /*<<< orphan*/  nfp_repr_inc_rx_stats (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  nn_dp_warn (struct nfp_net_dp*,char*,...) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_metadata_set (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xdp_exception (struct net_device*,struct bpf_prog*,int) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nfp_net_rx(struct nfp_net_rx_ring *rx_ring, int budget)
{
	struct nfp_net_r_vector *r_vec = rx_ring->r_vec;
	struct nfp_net_dp *dp = &r_vec->nfp_net->dp;
	struct nfp_net_tx_ring *tx_ring;
	struct bpf_prog *xdp_prog;
	bool xdp_tx_cmpl = false;
	unsigned int true_bufsz;
	struct sk_buff *skb;
	int pkts_polled = 0;
	struct xdp_buff xdp;
	int idx;

	rcu_read_lock();
	xdp_prog = READ_ONCE(dp->xdp_prog);
	true_bufsz = xdp_prog ? PAGE_SIZE : dp->fl_bufsz;
	xdp.rxq = &rx_ring->xdp_rxq;
	tx_ring = r_vec->xdp_ring;

	while (pkts_polled < budget) {
		unsigned int meta_len, data_len, meta_off, pkt_len, pkt_off;
		struct nfp_net_rx_buf *rxbuf;
		struct nfp_net_rx_desc *rxd;
		struct nfp_meta_parsed meta;
		bool redir_egress = false;
		struct net_device *netdev;
		dma_addr_t new_dma_addr;
		u32 meta_len_xdp = 0;
		void *new_frag;

		idx = D_IDX(rx_ring, rx_ring->rd_p);

		rxd = &rx_ring->rxds[idx];
		if (!(rxd->rxd.meta_len_dd & PCIE_DESC_RX_DD))
			break;

		/* Memory barrier to ensure that we won't do other reads
		 * before the DD bit.
		 */
		dma_rmb();

		memset(&meta, 0, sizeof(meta));

		rx_ring->rd_p++;
		pkts_polled++;

		rxbuf =	&rx_ring->rxbufs[idx];
		/*         < meta_len >
		 *  <-- [rx_offset] -->
		 *  ---------------------------------------------------------
		 * | [XX] |  metadata  |             packet           | XXXX |
		 *  ---------------------------------------------------------
		 *         <---------------- data_len --------------->
		 *
		 * The rx_offset is fixed for all packets, the meta_len can vary
		 * on a packet by packet basis. If rx_offset is set to zero
		 * (_RX_OFFSET_DYNAMIC) metadata starts at the beginning of the
		 * buffer and is immediately followed by the packet (no [XX]).
		 */
		meta_len = rxd->rxd.meta_len_dd & PCIE_DESC_RX_META_LEN_MASK;
		data_len = le16_to_cpu(rxd->rxd.data_len);
		pkt_len = data_len - meta_len;

		pkt_off = NFP_NET_RX_BUF_HEADROOM + dp->rx_dma_off;
		if (dp->rx_offset == NFP_NET_CFG_RX_OFFSET_DYNAMIC)
			pkt_off += meta_len;
		else
			pkt_off += dp->rx_offset;
		meta_off = pkt_off - meta_len;

		/* Stats update */
		u64_stats_update_begin(&r_vec->rx_sync);
		r_vec->rx_pkts++;
		r_vec->rx_bytes += pkt_len;
		u64_stats_update_end(&r_vec->rx_sync);

		if (unlikely(meta_len > NFP_NET_MAX_PREPEND ||
			     (dp->rx_offset && meta_len > dp->rx_offset))) {
			nn_dp_warn(dp, "oversized RX packet metadata %u\n",
				   meta_len);
			nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf, NULL);
			continue;
		}

		nfp_net_dma_sync_cpu_rx(dp, rxbuf->dma_addr + meta_off,
					data_len);

		if (!dp->chained_metadata_format) {
			nfp_net_set_hash_desc(dp->netdev, &meta,
					      rxbuf->frag + meta_off, rxd);
		} else if (meta_len) {
			void *end;

			end = nfp_net_parse_meta(dp->netdev, &meta,
						 rxbuf->frag + meta_off,
						 meta_len);
			if (unlikely(end != rxbuf->frag + pkt_off)) {
				nn_dp_warn(dp, "invalid RX packet metadata\n");
				nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf,
						NULL);
				continue;
			}
		}

		if (xdp_prog && !meta.portid) {
			void *orig_data = rxbuf->frag + pkt_off;
			unsigned int dma_off;
			int act;

			xdp.data_hard_start = rxbuf->frag + NFP_NET_RX_BUF_HEADROOM;
			xdp.data = orig_data;
			xdp.data_meta = orig_data;
			xdp.data_end = orig_data + pkt_len;

			act = bpf_prog_run_xdp(xdp_prog, &xdp);

			pkt_len = xdp.data_end - xdp.data;
			pkt_off += xdp.data - orig_data;

			switch (act) {
			case XDP_PASS:
				meta_len_xdp = xdp.data - xdp.data_meta;
				break;
			case XDP_TX:
				dma_off = pkt_off - NFP_NET_RX_BUF_HEADROOM;
				if (unlikely(!nfp_net_tx_xdp_buf(dp, rx_ring,
								 tx_ring, rxbuf,
								 dma_off,
								 pkt_len,
								 &xdp_tx_cmpl)))
					trace_xdp_exception(dp->netdev,
							    xdp_prog, act);
				continue;
			default:
				bpf_warn_invalid_xdp_action(act);
				/* fall through */
			case XDP_ABORTED:
				trace_xdp_exception(dp->netdev, xdp_prog, act);
				/* fall through */
			case XDP_DROP:
				nfp_net_rx_give_one(dp, rx_ring, rxbuf->frag,
						    rxbuf->dma_addr);
				continue;
			}
		}

		if (likely(!meta.portid)) {
			netdev = dp->netdev;
		} else if (meta.portid == NFP_META_PORT_ID_CTRL) {
			struct nfp_net *nn = netdev_priv(dp->netdev);

			nfp_app_ctrl_rx_raw(nn->app, rxbuf->frag + pkt_off,
					    pkt_len);
			nfp_net_rx_give_one(dp, rx_ring, rxbuf->frag,
					    rxbuf->dma_addr);
			continue;
		} else {
			struct nfp_net *nn;

			nn = netdev_priv(dp->netdev);
			netdev = nfp_app_dev_get(nn->app, meta.portid,
						 &redir_egress);
			if (unlikely(!netdev)) {
				nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf,
						NULL);
				continue;
			}

			if (nfp_netdev_is_nfp_repr(netdev))
				nfp_repr_inc_rx_stats(netdev, pkt_len);
		}

		skb = build_skb(rxbuf->frag, true_bufsz);
		if (unlikely(!skb)) {
			nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf, NULL);
			continue;
		}
		new_frag = nfp_net_napi_alloc_one(dp, &new_dma_addr);
		if (unlikely(!new_frag)) {
			nfp_net_rx_drop(dp, r_vec, rx_ring, rxbuf, skb);
			continue;
		}

		nfp_net_dma_unmap_rx(dp, rxbuf->dma_addr);

		nfp_net_rx_give_one(dp, rx_ring, new_frag, new_dma_addr);

		skb_reserve(skb, pkt_off);
		skb_put(skb, pkt_len);

		skb->mark = meta.mark;
		skb_set_hash(skb, meta.hash, meta.hash_type);

		skb_record_rx_queue(skb, rx_ring->idx);
		skb->protocol = eth_type_trans(skb, netdev);

		nfp_net_rx_csum(dp, r_vec, rxd, &meta, skb);

#ifdef CONFIG_TLS_DEVICE
		if (rxd->rxd.flags & PCIE_DESC_RX_DECRYPTED) {
			skb->decrypted = true;
			u64_stats_update_begin(&r_vec->rx_sync);
			r_vec->hw_tls_rx++;
			u64_stats_update_end(&r_vec->rx_sync);
		}
#endif

		if (rxd->rxd.flags & PCIE_DESC_RX_VLAN)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       le16_to_cpu(rxd->rxd.vlan));
		if (meta_len_xdp)
			skb_metadata_set(skb, meta_len_xdp);

		if (likely(!redir_egress)) {
			napi_gro_receive(&rx_ring->r_vec->napi, skb);
		} else {
			skb->dev = netdev;
			skb_reset_network_header(skb);
			__skb_push(skb, ETH_HLEN);
			dev_queue_xmit(skb);
		}
	}

	if (xdp_prog) {
		if (tx_ring->wr_ptr_add)
			nfp_net_tx_xmit_more_flush(tx_ring);
		else if (unlikely(tx_ring->wr_p != tx_ring->rd_p) &&
			 !xdp_tx_cmpl)
			if (!nfp_net_xdp_complete(tx_ring))
				pkts_polled = budget;
	}
	rcu_read_unlock();

	return pkts_polled;
}