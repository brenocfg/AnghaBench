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
struct mlx5_ib_multiport_info {int /*<<< orphan*/  unref_comp; scalar_t__ unaffiliate; int /*<<< orphan*/  mdev_refcnt; scalar_t__ is_master; } ;
struct mlx5_ib_dev {struct mlx5_ib_port* port; int /*<<< orphan*/  mdev; int /*<<< orphan*/  ib_dev; } ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int IB_LINK_LAYER_ETHERNET ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_mp_enabled (int /*<<< orphan*/ ) ; 
 int mlx5_ib_port_link_layer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mlx5_ib_put_native_port_mdev(struct mlx5_ib_dev *ibdev, u8 port_num)
{
	enum rdma_link_layer ll = mlx5_ib_port_link_layer(&ibdev->ib_dev,
							  port_num);
	struct mlx5_ib_multiport_info *mpi;
	struct mlx5_ib_port *port;

	if (!mlx5_core_mp_enabled(ibdev->mdev) || ll != IB_LINK_LAYER_ETHERNET)
		return;

	port = &ibdev->port[port_num - 1];

	spin_lock(&port->mp.mpi_lock);
	mpi = ibdev->port[port_num - 1].mp.mpi;
	if (mpi->is_master)
		goto out;

	mpi->mdev_refcnt--;
	if (mpi->unaffiliate)
		complete(&mpi->unref_comp);
out:
	spin_unlock(&port->mp.mpi_lock);
}