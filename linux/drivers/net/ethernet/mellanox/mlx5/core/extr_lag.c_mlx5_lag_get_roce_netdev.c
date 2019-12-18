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
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ tx_type; TYPE_1__* netdev_state; } ;
struct mlx5_lag {TYPE_3__* pf; TYPE_2__ tracker; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_6__ {struct net_device* netdev; } ;
struct TYPE_4__ {scalar_t__ tx_enabled; } ;

/* Variables and functions */
 scalar_t__ NETDEV_LAG_TX_TYPE_ACTIVEBACKUP ; 
 scalar_t__ __mlx5_lag_is_roce (struct mlx5_lag*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  lag_mutex ; 
 struct mlx5_lag* mlx5_lag_dev_get (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct net_device *mlx5_lag_get_roce_netdev(struct mlx5_core_dev *dev)
{
	struct net_device *ndev = NULL;
	struct mlx5_lag *ldev;

	mutex_lock(&lag_mutex);
	ldev = mlx5_lag_dev_get(dev);

	if (!(ldev && __mlx5_lag_is_roce(ldev)))
		goto unlock;

	if (ldev->tracker.tx_type == NETDEV_LAG_TX_TYPE_ACTIVEBACKUP) {
		ndev = ldev->tracker.netdev_state[0].tx_enabled ?
		       ldev->pf[0].netdev : ldev->pf[1].netdev;
	} else {
		ndev = ldev->pf[0].netdev;
	}
	if (ndev)
		dev_hold(ndev);

unlock:
	mutex_unlock(&lag_mutex);

	return ndev;
}