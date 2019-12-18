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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tls_context {struct net_device* netdev; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct net_device {int dummy; } ;
struct mlx5e_txqsq {struct mlx5e_sq_stats* stats; } ;
struct mlx5_wqe_ctrl_seg {int /*<<< orphan*/  tisn; } ;
struct mlx5e_tx_wqe {struct mlx5_wqe_ctrl_seg ctrl; } ;
struct mlx5e_sq_stats {int tls_encrypted_packets; int tls_encrypted_bytes; int /*<<< orphan*/  tls_ctx; } ;
struct mlx5e_ktls_offload_context_tx {scalar_t__ expected_seq; int tisn; } ;
typedef  enum mlx5e_ktls_sync_retval { ____Placeholder_mlx5e_ktls_sync_retval } mlx5e_ktls_sync_retval ;
struct TYPE_4__ {int gso_segs; } ;
struct TYPE_3__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int MLX5E_KTLS_SYNC_DONE ; 
 int MLX5E_KTLS_SYNC_FAIL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 struct mlx5e_ktls_offload_context_tx* mlx5e_get_ktls_tx_priv_ctx (struct tls_context*) ; 
 int mlx5e_ktls_tx_handle_ooo (struct mlx5e_ktls_offload_context_tx*,struct mlx5e_txqsq*,int,scalar_t__) ; 
 int mlx5e_ktls_tx_offload_test_and_clear_pending (struct mlx5e_ktls_offload_context_tx*) ; 
 int /*<<< orphan*/  mlx5e_ktls_tx_post_param_wqes (struct mlx5e_txqsq*,struct mlx5e_ktls_offload_context_tx*,int,int) ; 
 struct mlx5e_tx_wqe* mlx5e_sq_fetch_wqe (struct mlx5e_txqsq*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 TYPE_1__* tcp_hdr (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 struct tls_context* tls_get_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_is_sk_tx_device_offloaded (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *mlx5e_ktls_handle_tx_skb(struct net_device *netdev,
					 struct mlx5e_txqsq *sq,
					 struct sk_buff *skb,
					 struct mlx5e_tx_wqe **wqe, u16 *pi)
{
	struct mlx5e_ktls_offload_context_tx *priv_tx;
	struct mlx5e_sq_stats *stats = sq->stats;
	struct mlx5_wqe_ctrl_seg *cseg;
	struct tls_context *tls_ctx;
	int datalen;
	u32 seq;

	if (!skb->sk || !tls_is_sk_tx_device_offloaded(skb->sk))
		goto out;

	datalen = skb->len - (skb_transport_offset(skb) + tcp_hdrlen(skb));
	if (!datalen)
		goto out;

	tls_ctx = tls_get_ctx(skb->sk);
	if (WARN_ON_ONCE(tls_ctx->netdev != netdev))
		goto err_out;

	priv_tx = mlx5e_get_ktls_tx_priv_ctx(tls_ctx);

	if (unlikely(mlx5e_ktls_tx_offload_test_and_clear_pending(priv_tx))) {
		mlx5e_ktls_tx_post_param_wqes(sq, priv_tx, false, false);
		*wqe = mlx5e_sq_fetch_wqe(sq, sizeof(**wqe), pi);
		stats->tls_ctx++;
	}

	seq = ntohl(tcp_hdr(skb)->seq);
	if (unlikely(priv_tx->expected_seq != seq)) {
		enum mlx5e_ktls_sync_retval ret =
			mlx5e_ktls_tx_handle_ooo(priv_tx, sq, datalen, seq);

		if (likely(ret == MLX5E_KTLS_SYNC_DONE))
			*wqe = mlx5e_sq_fetch_wqe(sq, sizeof(**wqe), pi);
		else if (ret == MLX5E_KTLS_SYNC_FAIL)
			goto err_out;
		else /* ret == MLX5E_KTLS_SYNC_SKIP_NO_DATA */
			goto out;
	}

	priv_tx->expected_seq = seq + datalen;

	cseg = &(*wqe)->ctrl;
	cseg->tisn = cpu_to_be32(priv_tx->tisn << 8);

	stats->tls_encrypted_packets += skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1;
	stats->tls_encrypted_bytes   += datalen;

out:
	return skb;

err_out:
	dev_kfree_skb_any(skb);
	return NULL;
}