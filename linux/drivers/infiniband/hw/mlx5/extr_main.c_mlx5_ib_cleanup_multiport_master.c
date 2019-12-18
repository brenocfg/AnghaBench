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
struct mlx5_ib_dev {int num_ports; int /*<<< orphan*/  mdev; int /*<<< orphan*/  ib_dev_list; TYPE_2__* port; int /*<<< orphan*/  ib_dev; } ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;
struct TYPE_3__ {int /*<<< orphan*/ * mpi; } ;
struct TYPE_4__ {TYPE_1__ mp; } ;

/* Variables and functions */
 int IB_LINK_LAYER_ETHERNET ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_is_mp_master (int /*<<< orphan*/ ) ; 
 int mlx5_core_native_port_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_ib_multiport_mutex ; 
 int mlx5_ib_port_link_layer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_ib_unbind_slave_port (struct mlx5_ib_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_nic_vport_disable_roce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_ib_cleanup_multiport_master(struct mlx5_ib_dev *dev)
{
	int port_num = mlx5_core_native_port_num(dev->mdev) - 1;
	enum rdma_link_layer ll = mlx5_ib_port_link_layer(&dev->ib_dev,
							  port_num + 1);
	int i;

	if (!mlx5_core_is_mp_master(dev->mdev) || ll != IB_LINK_LAYER_ETHERNET)
		return;

	mutex_lock(&mlx5_ib_multiport_mutex);
	for (i = 0; i < dev->num_ports; i++) {
		if (dev->port[i].mp.mpi) {
			/* Destroy the native port stub */
			if (i == port_num) {
				kfree(dev->port[i].mp.mpi);
				dev->port[i].mp.mpi = NULL;
			} else {
				mlx5_ib_dbg(dev, "unbinding port_num: %d\n", i + 1);
				mlx5_ib_unbind_slave_port(dev, dev->port[i].mp.mpi);
			}
		}
	}

	mlx5_ib_dbg(dev, "removing from devlist\n");
	list_del(&dev->ib_dev_list);
	mutex_unlock(&mlx5_ib_multiport_mutex);

	mlx5_nic_vport_disable_roce(dev->mdev);
}