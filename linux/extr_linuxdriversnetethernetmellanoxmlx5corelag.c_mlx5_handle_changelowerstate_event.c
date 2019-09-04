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
struct netdev_notifier_changelowerstate_info {struct netdev_lag_lower_state_info* lower_state_info; } ;
struct netdev_lag_lower_state_info {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5_lag {int dummy; } ;
struct lag_tracker {struct netdev_lag_lower_state_info* netdev_state; } ;

/* Variables and functions */
 int mlx5_lag_dev_get_netdev_idx (struct mlx5_lag*,struct net_device*) ; 
 int /*<<< orphan*/  netif_is_lag_port (struct net_device*) ; 

__attribute__((used)) static int mlx5_handle_changelowerstate_event(struct mlx5_lag *ldev,
					      struct lag_tracker *tracker,
					      struct net_device *ndev,
					      struct netdev_notifier_changelowerstate_info *info)
{
	struct netdev_lag_lower_state_info *lag_lower_info;
	int idx;

	if (!netif_is_lag_port(ndev))
		return 0;

	idx = mlx5_lag_dev_get_netdev_idx(ldev, ndev);
	if (idx == -1)
		return 0;

	/* This information is used to determine virtual to physical
	 * port mapping.
	 */
	lag_lower_info = info->lower_state_info;
	if (!lag_lower_info)
		return 0;

	tracker->netdev_state[idx] = *lag_lower_info;

	return 1;
}