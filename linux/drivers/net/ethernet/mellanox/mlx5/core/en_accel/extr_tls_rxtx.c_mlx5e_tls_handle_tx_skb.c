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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tls_context {struct net_device* netdev; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct net_device {int dummy; } ;
struct mlx5e_txqsq {TYPE_1__* channel; } ;
struct mlx5e_tx_wqe {int dummy; } ;
struct mlx5e_tls_offload_context_tx {scalar_t__ expected_seq; int /*<<< orphan*/  swid; } ;
struct mlx5e_priv {TYPE_4__* tls; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_tls_drop_metadata; } ;
struct TYPE_8__ {TYPE_2__ sw_stats; } ;
struct TYPE_7__ {int /*<<< orphan*/  seq; } ;
struct TYPE_5__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct mlx5e_tls_offload_context_tx* mlx5e_get_tls_tx_context (struct tls_context*) ; 
 struct sk_buff* mlx5e_ktls_handle_tx_skb (struct net_device*,struct mlx5e_txqsq*,struct sk_buff*,struct mlx5e_tx_wqe**,int /*<<< orphan*/ *) ; 
 int mlx5e_tls_add_metadata (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* mlx5e_tls_handle_ooo (struct mlx5e_tls_offload_context_tx*,struct mlx5e_txqsq*,struct sk_buff*,struct mlx5e_tx_wqe**,int /*<<< orphan*/ *,TYPE_4__*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 TYPE_3__* tcp_hdr (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  tls ; 
 struct tls_context* tls_get_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_is_sk_tx_device_offloaded (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *mlx5e_tls_handle_tx_skb(struct net_device *netdev,
					struct mlx5e_txqsq *sq,
					struct sk_buff *skb,
					struct mlx5e_tx_wqe **wqe,
					u16 *pi)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_tls_offload_context_tx *context;
	struct tls_context *tls_ctx;
	u32 expected_seq;
	int datalen;
	u32 skb_seq;

	if (MLX5_CAP_GEN(sq->channel->mdev, tls)) {
		skb = mlx5e_ktls_handle_tx_skb(netdev, sq, skb, wqe, pi);
		goto out;
	}

	if (!skb->sk || !tls_is_sk_tx_device_offloaded(skb->sk))
		goto out;

	datalen = skb->len - (skb_transport_offset(skb) + tcp_hdrlen(skb));
	if (!datalen)
		goto out;

	tls_ctx = tls_get_ctx(skb->sk);
	if (unlikely(tls_ctx->netdev != netdev))
		goto out;

	skb_seq = ntohl(tcp_hdr(skb)->seq);
	context = mlx5e_get_tls_tx_context(tls_ctx);
	expected_seq = context->expected_seq;

	if (unlikely(expected_seq != skb_seq)) {
		skb = mlx5e_tls_handle_ooo(context, sq, skb, wqe, pi, priv->tls);
		goto out;
	}

	if (unlikely(mlx5e_tls_add_metadata(skb, context->swid))) {
		atomic64_inc(&priv->tls->sw_stats.tx_tls_drop_metadata);
		dev_kfree_skb_any(skb);
		skb = NULL;
		goto out;
	}

	context->expected_seq = skb_seq + datalen;
out:
	return skb;
}