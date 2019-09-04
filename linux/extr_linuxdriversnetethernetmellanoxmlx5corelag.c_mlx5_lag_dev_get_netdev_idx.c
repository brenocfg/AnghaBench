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
struct net_device {int dummy; } ;
struct mlx5_lag {TYPE_1__* pf; } ;
struct TYPE_2__ {struct net_device* netdev; } ;

/* Variables and functions */
 int MLX5_MAX_PORTS ; 

__attribute__((used)) static int mlx5_lag_dev_get_netdev_idx(struct mlx5_lag *ldev,
				       struct net_device *ndev)
{
	int i;

	for (i = 0; i < MLX5_MAX_PORTS; i++)
		if (ldev->pf[i].netdev == ndev)
			return i;

	return -1;
}