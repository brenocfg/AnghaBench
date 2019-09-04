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
typedef  size_t u8 ;
struct mlx5_ib_multiport_info {int /*<<< orphan*/  mdev; struct mlx5_ib_dev* ibdev; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; TYPE_2__* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  mpi_lock; struct mlx5_ib_multiport_info* mpi; } ;
struct TYPE_4__ {TYPE_1__ mp; } ;

/* Variables and functions */
 int get_port_caps (struct mlx5_ib_dev*,size_t) ; 
 int mlx5_add_netdev_notifier (struct mlx5_ib_dev*,size_t) ; 
 size_t mlx5_core_native_port_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,size_t) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,size_t) ; 
 int mlx5_ib_init_cong_debugfs (struct mlx5_ib_dev*,size_t) ; 
 int /*<<< orphan*/  mlx5_ib_unbind_slave_port (struct mlx5_ib_dev*,struct mlx5_ib_multiport_info*) ; 
 int mlx5_nic_vport_affiliate_multiport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mlx5_ib_bind_slave_port(struct mlx5_ib_dev *ibdev,
				    struct mlx5_ib_multiport_info *mpi)
{
	u8 port_num = mlx5_core_native_port_num(mpi->mdev) - 1;
	int err;

	spin_lock(&ibdev->port[port_num].mp.mpi_lock);
	if (ibdev->port[port_num].mp.mpi) {
		mlx5_ib_dbg(ibdev, "port %d already affiliated.\n",
			    port_num + 1);
		spin_unlock(&ibdev->port[port_num].mp.mpi_lock);
		return false;
	}

	ibdev->port[port_num].mp.mpi = mpi;
	mpi->ibdev = ibdev;
	spin_unlock(&ibdev->port[port_num].mp.mpi_lock);

	err = mlx5_nic_vport_affiliate_multiport(ibdev->mdev, mpi->mdev);
	if (err)
		goto unbind;

	err = get_port_caps(ibdev, mlx5_core_native_port_num(mpi->mdev));
	if (err)
		goto unbind;

	err = mlx5_add_netdev_notifier(ibdev, port_num);
	if (err) {
		mlx5_ib_err(ibdev, "failed adding netdev notifier for port %u\n",
			    port_num + 1);
		goto unbind;
	}

	err = mlx5_ib_init_cong_debugfs(ibdev, port_num);
	if (err)
		goto unbind;

	return true;

unbind:
	mlx5_ib_unbind_slave_port(ibdev, mpi);
	return false;
}