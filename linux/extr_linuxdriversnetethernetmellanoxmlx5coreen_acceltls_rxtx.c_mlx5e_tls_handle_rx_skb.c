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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int decrypted; scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int syndrome; } ;
struct TYPE_5__ {TYPE_4__ recv; } ;
struct mlx5e_tls_metadata {TYPE_1__ content; } ;
struct mlx5e_priv {TYPE_3__* tls; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_tls_auth_fail; int /*<<< orphan*/  rx_tls_resync_request; } ;
struct TYPE_7__ {TYPE_2__ sw_stats; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 scalar_t__ MLX5E_METADATA_ETHER_LEN ; 
#define  SYNDROM_AUTH_FAILED 130 
#define  SYNDROM_DECRYPTED 129 
#define  SYNDROM_RESYNC_REQUEST 128 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_metadata_hdr_valid (struct sk_buff*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  remove_metadata_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tls_update_resync_sn (struct net_device*,struct sk_buff*,struct mlx5e_tls_metadata*) ; 

void mlx5e_tls_handle_rx_skb(struct net_device *netdev, struct sk_buff *skb,
			     u32 *cqe_bcnt)
{
	struct mlx5e_tls_metadata *mdata;
	struct mlx5e_priv *priv;

	if (!is_metadata_hdr_valid(skb))
		return;

	/* Use the metadata */
	mdata = (struct mlx5e_tls_metadata *)(skb->data + ETH_HLEN);
	switch (mdata->content.recv.syndrome) {
	case SYNDROM_DECRYPTED:
		skb->decrypted = 1;
		break;
	case SYNDROM_RESYNC_REQUEST:
		tls_update_resync_sn(netdev, skb, mdata);
		priv = netdev_priv(netdev);
		atomic64_inc(&priv->tls->sw_stats.rx_tls_resync_request);
		break;
	case SYNDROM_AUTH_FAILED:
		/* Authentication failure will be observed and verified by kTLS */
		priv = netdev_priv(netdev);
		atomic64_inc(&priv->tls->sw_stats.rx_tls_auth_fail);
		break;
	default:
		/* Bypass the metadata header to others */
		return;
	}

	remove_metadata_hdr(skb);
	*cqe_bcnt -= MLX5E_METADATA_ETHER_LEN;
}