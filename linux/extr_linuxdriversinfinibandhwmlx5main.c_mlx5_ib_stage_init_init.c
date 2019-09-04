#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {struct mlx5_core_dev* dev; int /*<<< orphan*/  memic_lock; } ;
struct TYPE_15__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_16__ {int phys_port_cnt; TYPE_5__ dev; int /*<<< orphan*/  num_comp_vectors; scalar_t__ local_dma_lkey; int /*<<< orphan*/  node_type; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct mlx5_ib_dev {int num_ports; TYPE_9__* port; TYPE_8__ memic; int /*<<< orphan*/  reset_flow_resource_lock; int /*<<< orphan*/  qp_list; int /*<<< orphan*/  cap_mask_mutex; TYPE_6__ ib_dev; struct mlx5_core_dev* mdev; TYPE_2__* roce; } ;
struct TYPE_13__ {int /*<<< orphan*/  num_comp_vectors; } ;
struct TYPE_14__ {TYPE_3__ eq_table; } ;
struct mlx5_core_dev {TYPE_7__* pdev; TYPE_4__ priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  mpi_lock; } ;
struct TYPE_19__ {TYPE_1__ mp; } ;
struct TYPE_17__ {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  netdev_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_DEVICE_NAME_MAX ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RDMA_NODE_IB_CA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  get_ext_port_caps (struct mlx5_ib_dev*) ; 
 int get_port_caps (struct mlx5_ib_dev*,int) ; 
 TYPE_9__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_9__*) ; 
 int /*<<< orphan*/  mlx5_core_mp_enabled (struct mlx5_core_dev*) ; 
 int mlx5_core_native_port_num (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_cleanup_multiport_master (struct mlx5_ib_dev*) ; 
 int mlx5_ib_init_multiport_master (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_lag_is_active (struct mlx5_core_dev*) ; 
 scalar_t__ mlx5_use_mad_ifc (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int mlx5_ib_stage_init_init(struct mlx5_ib_dev *dev)
{
	struct mlx5_core_dev *mdev = dev->mdev;
	const char *name;
	int err;
	int i;

	dev->port = kcalloc(dev->num_ports, sizeof(*dev->port),
			    GFP_KERNEL);
	if (!dev->port)
		return -ENOMEM;

	for (i = 0; i < dev->num_ports; i++) {
		spin_lock_init(&dev->port[i].mp.mpi_lock);
		rwlock_init(&dev->roce[i].netdev_lock);
	}

	err = mlx5_ib_init_multiport_master(dev);
	if (err)
		goto err_free_port;

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

	if (!mlx5_lag_is_active(mdev))
		name = "mlx5_%d";
	else
		name = "mlx5_bond_%d";

	strlcpy(dev->ib_dev.name, name, IB_DEVICE_NAME_MAX);
	dev->ib_dev.owner		= THIS_MODULE;
	dev->ib_dev.node_type		= RDMA_NODE_IB_CA;
	dev->ib_dev.local_dma_lkey	= 0 /* not supported for now */;
	dev->ib_dev.phys_port_cnt	= dev->num_ports;
	dev->ib_dev.num_comp_vectors    =
		dev->mdev->priv.eq_table.num_comp_vectors;
	dev->ib_dev.dev.parent		= &mdev->pdev->dev;

	mutex_init(&dev->cap_mask_mutex);
	INIT_LIST_HEAD(&dev->qp_list);
	spin_lock_init(&dev->reset_flow_resource_lock);

	spin_lock_init(&dev->memic.memic_lock);
	dev->memic.dev = mdev;

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	err = init_srcu_struct(&dev->mr_srcu);
	if (err)
		goto err_free_port;
#endif

	return 0;
err_mp:
	mlx5_ib_cleanup_multiport_master(dev);

err_free_port:
	kfree(dev->port);

	return -ENOMEM;
}