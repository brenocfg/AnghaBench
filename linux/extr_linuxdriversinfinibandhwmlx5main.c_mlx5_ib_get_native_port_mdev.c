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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  mpi_lock; struct mlx5_ib_multiport_info* mpi; } ;
struct mlx5_ib_port {TYPE_1__ mp; } ;
struct mlx5_ib_multiport_info {int /*<<< orphan*/  mdev_refcnt; int /*<<< orphan*/  is_master; struct mlx5_core_dev* mdev; int /*<<< orphan*/  unaffiliate; } ;
struct mlx5_ib_dev {struct mlx5_ib_port* port; struct mlx5_core_dev* mdev; int /*<<< orphan*/  ib_dev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int IB_LINK_LAYER_ETHERNET ; 
 int /*<<< orphan*/  mlx5_core_mp_enabled (struct mlx5_core_dev*) ; 
 int mlx5_ib_port_link_layer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct mlx5_core_dev *mlx5_ib_get_native_port_mdev(struct mlx5_ib_dev *ibdev,
						   u8 ib_port_num,
						   u8 *native_port_num)
{
	enum rdma_link_layer ll = mlx5_ib_port_link_layer(&ibdev->ib_dev,
							  ib_port_num);
	struct mlx5_core_dev *mdev = NULL;
	struct mlx5_ib_multiport_info *mpi;
	struct mlx5_ib_port *port;

	if (!mlx5_core_mp_enabled(ibdev->mdev) ||
	    ll != IB_LINK_LAYER_ETHERNET) {
		if (native_port_num)
			*native_port_num = ib_port_num;
		return ibdev->mdev;
	}

	if (native_port_num)
		*native_port_num = 1;

	port = &ibdev->port[ib_port_num - 1];
	if (!port)
		return NULL;

	spin_lock(&port->mp.mpi_lock);
	mpi = ibdev->port[ib_port_num - 1].mp.mpi;
	if (mpi && !mpi->unaffiliate) {
		mdev = mpi->mdev;
		/* If it's the master no need to refcount, it'll exist
		 * as long as the ib_dev exists.
		 */
		if (!mpi->is_master)
			mpi->mdev_refcnt++;
	}
	spin_unlock(&port->mp.mpi_lock);

	return mdev;
}