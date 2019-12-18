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
struct net_device {int features; } ;
struct TYPE_5__ {int /*<<< orphan*/  active_svlans; } ;
struct TYPE_6__ {TYPE_2__ vlan; } ;
struct mlx5e_params {int /*<<< orphan*/  vlan_strip_disable; } ;
struct TYPE_4__ {struct mlx5e_params params; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; TYPE_3__ fs; TYPE_1__ channels; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 scalar_t__ MLX5E_GET_PFLAG (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_CQE_COMPRESS ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_STRIDING_RQ ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_LRO ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  VLAN_N_VID ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 

__attribute__((used)) static netdev_features_t mlx5e_fix_features(struct net_device *netdev,
					    netdev_features_t features)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_params *params;

	mutex_lock(&priv->state_lock);
	params = &priv->channels.params;
	if (!bitmap_empty(priv->fs.vlan.active_svlans, VLAN_N_VID)) {
		/* HW strips the outer C-tag header, this is a problem
		 * for S-tag traffic.
		 */
		features &= ~NETIF_F_HW_VLAN_CTAG_RX;
		if (!params->vlan_strip_disable)
			netdev_warn(netdev, "Dropping C-tag vlan stripping offload due to S-tag vlan\n");
	}
	if (!MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_STRIDING_RQ)) {
		if (features & NETIF_F_LRO) {
			netdev_warn(netdev, "Disabling LRO, not supported in legacy RQ\n");
			features &= ~NETIF_F_LRO;
		}
	}

	if (MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_CQE_COMPRESS)) {
		features &= ~NETIF_F_RXHASH;
		if (netdev->features & NETIF_F_RXHASH)
			netdev_warn(netdev, "Disabling rxhash, not supported when CQE compress is active\n");
	}

	mutex_unlock(&priv->state_lock);

	return features;
}