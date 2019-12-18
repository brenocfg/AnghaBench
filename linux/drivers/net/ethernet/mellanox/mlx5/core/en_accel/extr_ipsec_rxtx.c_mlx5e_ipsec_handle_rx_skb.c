#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_state {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct mlx5e_ipsec_metadata {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 scalar_t__ MLX5E_METADATA_ETHER_LEN ; 
 int /*<<< orphan*/  is_metadata_hdr_valid (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct xfrm_state* mlx5e_ipsec_build_sp (struct net_device*,struct sk_buff*,struct mlx5e_ipsec_metadata*) ; 
 int /*<<< orphan*/  remove_metadata_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *mlx5e_ipsec_handle_rx_skb(struct net_device *netdev,
					  struct sk_buff *skb, u32 *cqe_bcnt)
{
	struct mlx5e_ipsec_metadata *mdata;
	struct xfrm_state *xs;

	if (!is_metadata_hdr_valid(skb))
		return skb;

	/* Use the metadata */
	mdata = (struct mlx5e_ipsec_metadata *)(skb->data + ETH_HLEN);
	xs = mlx5e_ipsec_build_sp(netdev, skb, mdata);
	if (unlikely(!xs)) {
		kfree_skb(skb);
		return NULL;
	}

	remove_metadata_hdr(skb);
	*cqe_bcnt -= MLX5E_METADATA_ETHER_LEN;

	return skb;
}