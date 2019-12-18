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
struct sk_buff {scalar_t__ ip_summed; scalar_t__ encapsulation; } ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {scalar_t__ vxlan_port; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {int version; } ;
struct TYPE_3__ {scalar_t__ dest; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int NETIF_F_CSUM_MASK ; 
 int NETIF_F_GSO_MASK ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 TYPE_1__* udp_hdr (struct sk_buff*) ; 
 int vlan_features_check (struct sk_buff*,int) ; 
 int vxlan_features_check (struct sk_buff*,int) ; 

__attribute__((used)) static netdev_features_t mlx4_en_features_check(struct sk_buff *skb,
						struct net_device *dev,
						netdev_features_t features)
{
	features = vlan_features_check(skb, features);
	features = vxlan_features_check(skb, features);

	/* The ConnectX-3 doesn't support outer IPv6 checksums but it does
	 * support inner IPv6 checksums and segmentation so  we need to
	 * strip that feature if this is an IPv6 encapsulated frame.
	 */
	if (skb->encapsulation &&
	    (skb->ip_summed == CHECKSUM_PARTIAL)) {
		struct mlx4_en_priv *priv = netdev_priv(dev);

		if (!priv->vxlan_port ||
		    (ip_hdr(skb)->version != 4) ||
		    (udp_hdr(skb)->dest != priv->vxlan_port))
			features &= ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
	}

	return features;
}