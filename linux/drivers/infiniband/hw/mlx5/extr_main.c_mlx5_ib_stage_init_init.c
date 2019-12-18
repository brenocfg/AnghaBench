#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct mlx5_core_dev* dev; int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct TYPE_11__ {int phys_port_cnt; TYPE_4__ dev; int /*<<< orphan*/  num_comp_vectors; scalar_t__ local_dma_lkey; int /*<<< orphan*/  node_type; } ;
struct mlx5_ib_dev {int num_ports; int /*<<< orphan*/  mr_srcu; TYPE_6__ dm; int /*<<< orphan*/  reset_flow_resource_lock; int /*<<< orphan*/  qp_list; int /*<<< orphan*/  cap_mask_mutex; TYPE_5__ ib_dev; TYPE_3__* port; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int /*<<< orphan*/  device; } ;
struct TYPE_8__ {int native_port_num; int /*<<< orphan*/  last_port_state; struct mlx5_ib_dev* dev; int /*<<< orphan*/  netdev_lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  mpi_lock; } ;
struct TYPE_9__ {TYPE_2__ roce; TYPE_1__ mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INFINIBAND_ON_DEMAND_PAGING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IB_PORT_DOWN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_NODE_IB_CA ; 
 int /*<<< orphan*/  get_ext_port_caps (struct mlx5_ib_dev*) ; 
 int get_port_caps (struct mlx5_ib_dev*,int) ; 
 int init_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_comp_vectors_count (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_mp_enabled (struct mlx5_core_dev*) ; 
 int mlx5_core_native_port_num (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_cleanup_multiport_master (struct mlx5_ib_dev*) ; 
 int mlx5_ib_init_multiport_master (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_internal_fill_odp_caps (struct mlx5_ib_dev*) ; 
 scalar_t__ mlx5_use_mad_ifc (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int set_has_smi_cap (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_ib_stage_init_init(struct mlx5_ib_dev *dev)
{
	struct mlx5_core_dev *mdev = dev->mdev;
	int err;
	int i;

	for (i = 0; i < dev->num_ports; i++) {
		spin_lock_init(&dev->port[i].mp.mpi_lock);
		rwlock_init(&dev->port[i].roce.netdev_lock);
		dev->port[i].roce.dev = dev;
		dev->port[i].roce.native_port_num = i + 1;
		dev->port[i].roce.last_port_state = IB_PORT_DOWN;
	}

	mlx5_ib_internal_fill_odp_caps(dev);

	err = mlx5_ib_init_multiport_master(dev);
	if (err)
		return err;

	err = set_has_smi_cap(dev);
	if (err)
		return err;

	if (!mlx5_core_mp_enabled(mdev)) {
		for (i = 1; i <= dev->num_ports; i++) {
			err = get_port_caps(dev, i);
			if (err)
				break;
		}
	} else {
		err = get_port_caps(dev, mlx5_core_native_port_num(mdev));
	}
	if (err)
		goto err_mp;

	if (mlx5_use_mad_ifc(dev))
		get_ext_port_caps(dev);

	dev->ib_dev.node_type		= RDMA_NODE_IB_CA;
	dev->ib_dev.local_dma_lkey	= 0 /* not supported for now */;
	dev->ib_dev.phys_port_cnt	= dev->num_ports;
	dev->ib_dev.num_comp_vectors    = mlx5_comp_vectors_count(mdev);
	dev->ib_dev.dev.parent		= mdev->device;

	mutex_init(&dev->cap_mask_mutex);
	INIT_LIST_HEAD(&dev->qp_list);
	spin_lock_init(&dev->reset_flow_resource_lock);

	spin_lock_init(&dev->dm.lock);
	dev->dm.dev = mdev;

	if (IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING)) {
		err = init_srcu_struct(&dev->mr_srcu);
		if (err)
			goto err_mp;
	}

	return 0;

err_mp:
	mlx5_ib_cleanup_multiport_master(dev);

	return -ENOMEM;
}