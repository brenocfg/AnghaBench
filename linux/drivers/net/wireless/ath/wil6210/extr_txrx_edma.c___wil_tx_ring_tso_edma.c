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
typedef  union wil_tx_desc {int dummy; } wil_tx_desc ;
typedef  int u32 ;
struct wil_tx_enhanced_desc {int dummy; } ;
struct wil_ring_tx_data {scalar_t__ last_idle; int /*<<< orphan*/  idle; int /*<<< orphan*/  enabled; } ;
struct wil_ring {int swhead; int size; struct wil_ctx* ctx; TYPE_2__* va; int /*<<< orphan*/  hwtail; } ;
struct wil_ctx {int dummy; } ;
struct wil6210_vif {int dummy; } ;
struct wil6210_priv {scalar_t__ tx_latency; int /*<<< orphan*/  ring_idle_trsh; struct wil_ring_tx_data* ring_tx_data; struct wil_ring* ring_tx; } ;
struct sk_buff {int len; scalar_t__ ip_summed; struct wil_ctx* cb; int /*<<< orphan*/ * data; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_6__ {int nr_frags; int gso_size; int gso_type; int /*<<< orphan*/ * frags; } ;
struct TYPE_4__ {int /*<<< orphan*/  enhanced; } ;
struct TYPE_5__ {TYPE_1__ tx; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_HLEN ; 
#define  SKB_GSO_TCPV4 129 
#define  SKB_GSO_TCPV6 128 
 scalar_t__ get_cycles () ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  memset (struct wil_ctx*,int /*<<< orphan*/ ,int) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 int skb_headlen (struct sk_buff*) ; 
 int skb_network_header_len (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wil_dbg_txrx (struct wil6210_priv*,char*,int,...) ; 
 int /*<<< orphan*/  wil_err_ratelimited (struct wil6210_priv*,char*,int,int) ; 
 int /*<<< orphan*/  wil_ring_advance_head (struct wil_ring*,int) ; 
 int wil_ring_avail_tx (struct wil_ring*) ; 
 int wil_ring_used_tx (struct wil_ring*) ; 
 struct device* wil_to_dev (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_tso_type_first ; 
 int /*<<< orphan*/  wil_tso_type_hdr ; 
 int /*<<< orphan*/  wil_tso_type_lst ; 
 int /*<<< orphan*/  wil_tso_type_mid ; 
 int /*<<< orphan*/  wil_tx_desc_unmap_edma (struct device*,union wil_tx_desc*,struct wil_ctx*) ; 
 int wil_tx_tso_gen_desc (struct wil6210_priv*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wil_ring*,struct sk_buff*,int,int,int,int,int*) ; 
 scalar_t__ wil_val_in_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wil_w (struct wil6210_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int __wil_tx_ring_tso_edma(struct wil6210_priv *wil,
				  struct wil6210_vif *vif,
				  struct wil_ring *ring,
				  struct sk_buff *skb)
{
	int ring_index = ring - wil->ring_tx;
	struct wil_ring_tx_data *txdata = &wil->ring_tx_data[ring_index];
	int nr_frags = skb_shinfo(skb)->nr_frags;
	int min_desc_required = nr_frags + 2; /* Headers, Head, Fragments */
	int used, avail = wil_ring_avail_tx(ring);
	int f, hdrlen, headlen;
	int gso_type;
	bool is_ipv4;
	u32 swhead = ring->swhead;
	int descs_used = 0; /* total number of used descriptors */
	int rc = -EINVAL;
	int tcp_hdr_len;
	int skb_net_hdr_len;
	int mss = skb_shinfo(skb)->gso_size;

	wil_dbg_txrx(wil, "tx_ring_tso: %d bytes to ring %d\n", skb->len,
		     ring_index);

	if (unlikely(!txdata->enabled))
		return -EINVAL;

	if (unlikely(avail < min_desc_required)) {
		wil_err_ratelimited(wil,
				    "TSO: Tx ring[%2d] full. No space for %d fragments\n",
				    ring_index, min_desc_required);
		return -ENOMEM;
	}

	gso_type = skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV6 | SKB_GSO_TCPV4);
	switch (gso_type) {
	case SKB_GSO_TCPV4:
		is_ipv4 = true;
		break;
	case SKB_GSO_TCPV6:
		is_ipv4 = false;
		break;
	default:
		return -EINVAL;
	}

	if (skb->ip_summed != CHECKSUM_PARTIAL)
		return -EINVAL;

	/* tcp header length and skb network header length are fixed for all
	 * packet's descriptors - read them once here
	 */
	tcp_hdr_len = tcp_hdrlen(skb);
	skb_net_hdr_len = skb_network_header_len(skb);

	/* First descriptor must contain the header only
	 * Header Length = MAC header len + IP header len + TCP header len
	 */
	hdrlen = ETH_HLEN + tcp_hdr_len + skb_net_hdr_len;
	wil_dbg_txrx(wil, "TSO: process header descriptor, hdrlen %u\n",
		     hdrlen);
	rc = wil_tx_tso_gen_desc(wil, skb->data, hdrlen, swhead,
				 wil_tso_type_hdr, NULL, ring, skb,
				 is_ipv4, tcp_hdr_len, skb_net_hdr_len,
				 mss, &descs_used);
	if (rc)
		return -EINVAL;

	/* Second descriptor contains the head */
	headlen = skb_headlen(skb) - hdrlen;
	wil_dbg_txrx(wil, "TSO: process skb head, headlen %u\n", headlen);
	rc = wil_tx_tso_gen_desc(wil, skb->data + hdrlen, headlen,
				 (swhead + descs_used) % ring->size,
				 (nr_frags != 0) ? wil_tso_type_first :
				 wil_tso_type_lst, NULL, ring, skb,
				 is_ipv4, tcp_hdr_len, skb_net_hdr_len,
				 mss, &descs_used);
	if (rc)
		goto mem_error;

	/* Rest of the descriptors are from the SKB fragments */
	for (f = 0; f < nr_frags; f++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[f];
		int len = skb_frag_size(frag);

		wil_dbg_txrx(wil, "TSO: frag[%d]: len %u, descs_used %d\n", f,
			     len, descs_used);

		rc = wil_tx_tso_gen_desc(wil, NULL, len,
					 (swhead + descs_used) % ring->size,
					 (f != nr_frags - 1) ?
					 wil_tso_type_mid : wil_tso_type_lst,
					 frag, ring, skb, is_ipv4,
					 tcp_hdr_len, skb_net_hdr_len,
					 mss, &descs_used);
		if (rc)
			goto mem_error;
	}

	/* performance monitoring */
	used = wil_ring_used_tx(ring);
	if (wil_val_in_range(wil->ring_idle_trsh,
			     used, used + descs_used)) {
		txdata->idle += get_cycles() - txdata->last_idle;
		wil_dbg_txrx(wil,  "Ring[%2d] not idle %d -> %d\n",
			     ring_index, used, used + descs_used);
	}

	/* advance swhead */
	wil_ring_advance_head(ring, descs_used);
	wil_dbg_txrx(wil, "TSO: Tx swhead %d -> %d\n", swhead, ring->swhead);

	/* make sure all writes to descriptors (shared memory) are done before
	 * committing them to HW
	 */
	wmb();

	if (wil->tx_latency)
		*(ktime_t *)&skb->cb = ktime_get();
	else
		memset(skb->cb, 0, sizeof(ktime_t));

	wil_w(wil, ring->hwtail, ring->swhead);

	return 0;

mem_error:
	while (descs_used > 0) {
		struct device *dev = wil_to_dev(wil);
		struct wil_ctx *ctx;
		int i = (swhead + descs_used - 1) % ring->size;
		struct wil_tx_enhanced_desc dd, *d = &dd;
		struct wil_tx_enhanced_desc *_desc =
			(struct wil_tx_enhanced_desc *)
			&ring->va[i].tx.enhanced;

		*d = *_desc;
		ctx = &ring->ctx[i];
		wil_tx_desc_unmap_edma(dev, (union wil_tx_desc *)d, ctx);
		memset(ctx, 0, sizeof(*ctx));
		descs_used--;
	}
	return rc;
}