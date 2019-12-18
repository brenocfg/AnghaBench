#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int features; } ;
struct TYPE_2__ {int /*<<< orphan*/  maybe_stop_tx; int /*<<< orphan*/  fill_desc; } ;
struct hns_nic_priv {int enet_ver; TYPE_1__ ops; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
#define  AE_VERSION_1 128 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  fill_tso_desc ; 
 int /*<<< orphan*/  fill_v2_desc ; 
 int /*<<< orphan*/  hns_nic_maybe_stop_tso ; 
 int /*<<< orphan*/  hns_nic_maybe_stop_tx ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_gso_max_size (struct net_device*,int) ; 

__attribute__((used)) static int hns_nic_set_features(struct net_device *netdev,
				netdev_features_t features)
{
	struct hns_nic_priv *priv = netdev_priv(netdev);

	switch (priv->enet_ver) {
	case AE_VERSION_1:
		if (features & (NETIF_F_TSO | NETIF_F_TSO6))
			netdev_info(netdev, "enet v1 do not support tso!\n");
		break;
	default:
		if (features & (NETIF_F_TSO | NETIF_F_TSO6)) {
			priv->ops.fill_desc = fill_tso_desc;
			priv->ops.maybe_stop_tx = hns_nic_maybe_stop_tso;
			/* The chip only support 7*4096 */
			netif_set_gso_max_size(netdev, 7 * 4096);
		} else {
			priv->ops.fill_desc = fill_v2_desc;
			priv->ops.maybe_stop_tx = hns_nic_maybe_stop_tx;
		}
		break;
	}
	netdev->features = features;
	return 0;
}