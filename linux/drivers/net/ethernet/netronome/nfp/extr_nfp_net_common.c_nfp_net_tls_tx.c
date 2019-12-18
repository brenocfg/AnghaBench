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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  sk; } ;
struct nfp_net_tls_offload_ctx {scalar_t__ next_seq; int /*<<< orphan*/  fw_handle; } ;
struct nfp_net_r_vector {int /*<<< orphan*/  tx_sync; scalar_t__ hw_tls_tx; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tls_tx_no_fallback; int /*<<< orphan*/  tls_tx_fallback; } ;
struct nfp_net_dp {int /*<<< orphan*/  ktls_tx; } ;
struct TYPE_4__ {scalar_t__ gso_segs; } ;
struct TYPE_3__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_OFFLOAD_CTX_DIR_TX ; 
 int U32_MAX ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_dp_warn (struct nfp_net_dp*,char*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 TYPE_1__* tcp_hdr (struct sk_buff*) ; 
 scalar_t__ tcp_hdrlen (struct sk_buff*) ; 
 struct nfp_net_tls_offload_ctx* tls_driver_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* tls_encrypt_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  tls_is_sk_tx_device_offloaded (int /*<<< orphan*/ ) ; 
 int tls_offload_tx_resync_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_offload_tx_resync_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *
nfp_net_tls_tx(struct nfp_net_dp *dp, struct nfp_net_r_vector *r_vec,
	       struct sk_buff *skb, u64 *tls_handle, int *nr_frags)
{
#ifdef CONFIG_TLS_DEVICE
	struct nfp_net_tls_offload_ctx *ntls;
	struct sk_buff *nskb;
	bool resync_pending;
	u32 datalen, seq;

	if (likely(!dp->ktls_tx))
		return skb;
	if (!skb->sk || !tls_is_sk_tx_device_offloaded(skb->sk))
		return skb;

	datalen = skb->len - (skb_transport_offset(skb) + tcp_hdrlen(skb));
	seq = ntohl(tcp_hdr(skb)->seq);
	ntls = tls_driver_ctx(skb->sk, TLS_OFFLOAD_CTX_DIR_TX);
	resync_pending = tls_offload_tx_resync_pending(skb->sk);
	if (unlikely(resync_pending || ntls->next_seq != seq)) {
		/* Pure ACK out of order already */
		if (!datalen)
			return skb;

		u64_stats_update_begin(&r_vec->tx_sync);
		r_vec->tls_tx_fallback++;
		u64_stats_update_end(&r_vec->tx_sync);

		nskb = tls_encrypt_skb(skb);
		if (!nskb) {
			u64_stats_update_begin(&r_vec->tx_sync);
			r_vec->tls_tx_no_fallback++;
			u64_stats_update_end(&r_vec->tx_sync);
			return NULL;
		}
		/* encryption wasn't necessary */
		if (nskb == skb)
			return skb;
		/* we don't re-check ring space */
		if (unlikely(skb_is_nonlinear(nskb))) {
			nn_dp_warn(dp, "tls_encrypt_skb() produced fragmented frame\n");
			u64_stats_update_begin(&r_vec->tx_sync);
			r_vec->tx_errors++;
			u64_stats_update_end(&r_vec->tx_sync);
			dev_kfree_skb_any(nskb);
			return NULL;
		}

		/* jump forward, a TX may have gotten lost, need to sync TX */
		if (!resync_pending && seq - ntls->next_seq < U32_MAX / 4)
			tls_offload_tx_resync_request(nskb->sk);

		*nr_frags = 0;
		return nskb;
	}

	if (datalen) {
		u64_stats_update_begin(&r_vec->tx_sync);
		if (!skb_is_gso(skb))
			r_vec->hw_tls_tx++;
		else
			r_vec->hw_tls_tx += skb_shinfo(skb)->gso_segs;
		u64_stats_update_end(&r_vec->tx_sync);
	}

	memcpy(tls_handle, ntls->fw_handle, sizeof(ntls->fw_handle));
	ntls->next_seq += datalen;
#endif
	return skb;
}