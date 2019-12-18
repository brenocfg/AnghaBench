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
struct nfp_repr {TYPE_3__* dst; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {struct net_device* lower_dev; } ;
struct TYPE_5__ {TYPE_1__ port_info; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_HW_TC ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_SOFT_FEATURES ; 
 int netdev_intersect_features (int,int) ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t
nfp_repr_fix_features(struct net_device *netdev, netdev_features_t features)
{
	struct nfp_repr *repr = netdev_priv(netdev);
	netdev_features_t old_features = features;
	netdev_features_t lower_features;
	struct net_device *lower_dev;

	lower_dev = repr->dst->u.port_info.lower_dev;

	lower_features = lower_dev->features;
	if (lower_features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM))
		lower_features |= NETIF_F_HW_CSUM;

	features = netdev_intersect_features(features, lower_features);
	features |= old_features & (NETIF_F_SOFT_FEATURES | NETIF_F_HW_TC);
	features |= NETIF_F_LLTX;

	return features;
}