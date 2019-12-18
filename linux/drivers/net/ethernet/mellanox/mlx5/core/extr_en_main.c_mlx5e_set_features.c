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
struct net_device {int /*<<< orphan*/  features; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int EINVAL ; 
 int MLX5E_HANDLE_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_F_HW_TC ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  NETIF_F_LRO ; 
 int /*<<< orphan*/  NETIF_F_NTUPLE ; 
 int /*<<< orphan*/  NETIF_F_RXALL ; 
 int /*<<< orphan*/  NETIF_F_RXFCS ; 
 int /*<<< orphan*/  set_feature_arfs ; 
 int /*<<< orphan*/  set_feature_cvlan_filter ; 
 int /*<<< orphan*/  set_feature_lro ; 
 int /*<<< orphan*/  set_feature_rx_all ; 
 int /*<<< orphan*/  set_feature_rx_fcs ; 
 int /*<<< orphan*/  set_feature_rx_vlan ; 
 int /*<<< orphan*/  set_feature_tc_num_filters ; 

int mlx5e_set_features(struct net_device *netdev, netdev_features_t features)
{
	netdev_features_t oper_features = netdev->features;
	int err = 0;

#define MLX5E_HANDLE_FEATURE(feature, handler) \
	mlx5e_handle_feature(netdev, &oper_features, features, feature, handler)

	err |= MLX5E_HANDLE_FEATURE(NETIF_F_LRO, set_feature_lro);
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_HW_VLAN_CTAG_FILTER,
				    set_feature_cvlan_filter);
#ifdef CONFIG_MLX5_ESWITCH
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_HW_TC, set_feature_tc_num_filters);
#endif
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_RXALL, set_feature_rx_all);
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_RXFCS, set_feature_rx_fcs);
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_HW_VLAN_CTAG_RX, set_feature_rx_vlan);
#ifdef CONFIG_MLX5_EN_ARFS
	err |= MLX5E_HANDLE_FEATURE(NETIF_F_NTUPLE, set_feature_arfs);
#endif

	if (err) {
		netdev->features = oper_features;
		return -EINVAL;
	}

	return 0;
}