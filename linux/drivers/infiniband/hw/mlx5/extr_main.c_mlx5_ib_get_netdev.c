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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct mlx5_ib_dev {TYPE_2__* port; } ;
struct mlx5_core_dev {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  netdev_lock; struct net_device* netdev; } ;
struct TYPE_4__ {TYPE_1__ roce; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct mlx5_core_dev* mlx5_ib_get_native_port_mdev (struct mlx5_ib_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_put_native_port_mdev (struct mlx5_ib_dev*,int) ; 
 struct net_device* mlx5_lag_get_roce_netdev (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct net_device *mlx5_ib_get_netdev(struct ib_device *device,
					     u8 port_num)
{
	struct mlx5_ib_dev *ibdev = to_mdev(device);
	struct net_device *ndev;
	struct mlx5_core_dev *mdev;

	mdev = mlx5_ib_get_native_port_mdev(ibdev, port_num, NULL);
	if (!mdev)
		return NULL;

	ndev = mlx5_lag_get_roce_netdev(mdev);
	if (ndev)
		goto out;

	/* Ensure ndev does not disappear before we invoke dev_hold()
	 */
	read_lock(&ibdev->port[port_num - 1].roce.netdev_lock);
	ndev = ibdev->port[port_num - 1].roce.netdev;
	if (ndev)
		dev_hold(ndev);
	read_unlock(&ibdev->port[port_num - 1].roce.netdev_lock);

out:
	mlx5_ib_put_native_port_mdev(ibdev, port_num);
	return ndev;
}