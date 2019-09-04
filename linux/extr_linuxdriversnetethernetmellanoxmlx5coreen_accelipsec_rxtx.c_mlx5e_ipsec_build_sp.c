#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_state {int dummy; } ;
struct xfrm_offload {int /*<<< orphan*/  status; int /*<<< orphan*/  proto; int /*<<< orphan*/  flags; } ;
struct sk_buff {TYPE_4__* sp; } ;
struct net_device {int dummy; } ;
struct mlx5e_priv {TYPE_6__* ipsec; } ;
struct TYPE_7__ {int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  sa_handle; } ;
struct TYPE_8__ {TYPE_1__ rx; } ;
struct mlx5e_ipsec_metadata {int syndrome; TYPE_2__ content; } ;
struct TYPE_9__ {int /*<<< orphan*/  ipsec_rx_drop_syndrome; int /*<<< orphan*/  ipsec_rx_drop_sadb_miss; int /*<<< orphan*/  ipsec_rx_drop_sp_alloc; } ;
struct TYPE_11__ {TYPE_3__ sw_stats; int /*<<< orphan*/  no_trailer; } ;
struct TYPE_10__ {int /*<<< orphan*/  olen; int /*<<< orphan*/  len; struct xfrm_state** xvec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DONE ; 
 int /*<<< orphan*/  CRYPTO_INVALID_PROTOCOL ; 
 int /*<<< orphan*/  CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  CRYPTO_TUNNEL_ESP_AUTH_FAILED ; 
#define  MLX5E_IPSEC_RX_SYNDROME_AUTH_FAILED 130 
#define  MLX5E_IPSEC_RX_SYNDROME_BAD_PROTO 129 
#define  MLX5E_IPSEC_RX_SYNDROME_DECRYPTED 128 
 int /*<<< orphan*/  XFRM_ESP_NO_TRAILER ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 struct xfrm_state* mlx5e_ipsec_sadb_rx_lookup (TYPE_6__*,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 TYPE_4__* secpath_dup (TYPE_4__*) ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static inline struct xfrm_state *
mlx5e_ipsec_build_sp(struct net_device *netdev, struct sk_buff *skb,
		     struct mlx5e_ipsec_metadata *mdata)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct xfrm_offload *xo;
	struct xfrm_state *xs;
	u32 sa_handle;

	skb->sp = secpath_dup(skb->sp);
	if (unlikely(!skb->sp)) {
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_rx_drop_sp_alloc);
		return NULL;
	}

	sa_handle = be32_to_cpu(mdata->content.rx.sa_handle);
	xs = mlx5e_ipsec_sadb_rx_lookup(priv->ipsec, sa_handle);
	if (unlikely(!xs)) {
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_rx_drop_sadb_miss);
		return NULL;
	}

	skb->sp->xvec[skb->sp->len++] = xs;
	skb->sp->olen++;

	xo = xfrm_offload(skb);
	xo->flags = CRYPTO_DONE;
	switch (mdata->syndrome) {
	case MLX5E_IPSEC_RX_SYNDROME_DECRYPTED:
		xo->status = CRYPTO_SUCCESS;
		if (likely(priv->ipsec->no_trailer)) {
			xo->flags |= XFRM_ESP_NO_TRAILER;
			xo->proto = mdata->content.rx.nexthdr;
		}
		break;
	case MLX5E_IPSEC_RX_SYNDROME_AUTH_FAILED:
		xo->status = CRYPTO_TUNNEL_ESP_AUTH_FAILED;
		break;
	case MLX5E_IPSEC_RX_SYNDROME_BAD_PROTO:
		xo->status = CRYPTO_INVALID_PROTOCOL;
		break;
	default:
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_rx_drop_syndrome);
		return NULL;
	}
	return xs;
}