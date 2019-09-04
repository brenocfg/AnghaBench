#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_9__ {TYPE_3__* netdev_state; } ;
struct mlx5_lag {int /*<<< orphan*/  allowed; TYPE_4__ tracker; TYPE_2__* pf; } ;
struct TYPE_10__ {struct mlx5_lag* lag; } ;
struct mlx5_core_dev {TYPE_5__ priv; TYPE_1__* pdev; } ;
struct TYPE_8__ {scalar_t__ tx_enabled; scalar_t__ link_up; } ;
struct TYPE_7__ {struct net_device* netdev; struct mlx5_core_dev* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 unsigned int MLX5_MAX_PORTS ; 
 unsigned int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lag_mutex ; 
 int /*<<< orphan*/  mlx5_lag_check_prereq (struct mlx5_lag*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_lag_dev_add_pf(struct mlx5_lag *ldev,
				struct mlx5_core_dev *dev,
				struct net_device *netdev)
{
	unsigned int fn = PCI_FUNC(dev->pdev->devfn);

	if (fn >= MLX5_MAX_PORTS)
		return;

	mutex_lock(&lag_mutex);
	ldev->pf[fn].dev    = dev;
	ldev->pf[fn].netdev = netdev;
	ldev->tracker.netdev_state[fn].link_up = 0;
	ldev->tracker.netdev_state[fn].tx_enabled = 0;

	ldev->allowed = mlx5_lag_check_prereq(ldev);
	dev->priv.lag = ldev;

	mutex_unlock(&lag_mutex);
}