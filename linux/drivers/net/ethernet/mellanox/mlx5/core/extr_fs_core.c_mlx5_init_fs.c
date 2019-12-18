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
struct mlx5_flow_steering {void* fgs_cache; void* ftes_cache; struct mlx5_core_dev* dev; } ;
struct mlx5_flow_group {int dummy; } ;
struct TYPE_2__ {struct mlx5_flow_steering* steering; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct fs_fte {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MLX5_CAP_ESW_EGRESS_ACL (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_ESW_FLOWTABLE_FDB (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_ESW_INGRESS_ACL (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_FLOWTABLE_NIC_RX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_FLOWTABLE_NIC_TX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_FLOWTABLE_RDMA_RX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_FLOWTABLE_SNIFFER_RX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_FLOWTABLE_SNIFFER_TX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_IB ; 
 scalar_t__ MLX5_ESWITCH_MANAGER (struct mlx5_core_dev*) ; 
 scalar_t__ MLX5_IPSEC_DEV (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  ft_support ; 
 int init_egress_acls_root_ns (struct mlx5_core_dev*) ; 
 int init_egress_root_ns (struct mlx5_flow_steering*) ; 
 int init_fdb_root_ns (struct mlx5_flow_steering*) ; 
 int init_ingress_acls_root_ns (struct mlx5_core_dev*) ; 
 int init_rdma_rx_root_ns (struct mlx5_flow_steering*) ; 
 int init_root_ns (struct mlx5_flow_steering*) ; 
 int init_sniffer_rx_root_ns (struct mlx5_flow_steering*) ; 
 int init_sniffer_tx_root_ns (struct mlx5_flow_steering*) ; 
 int /*<<< orphan*/  ipoib_enhanced_offloads ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5_flow_steering* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_cleanup_fs (struct mlx5_core_dev*) ; 
 int mlx5_init_fc_stats (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  nic_flow_table ; 
 int /*<<< orphan*/  port_type ; 
 int /*<<< orphan*/  table_miss_action_domain ; 

int mlx5_init_fs(struct mlx5_core_dev *dev)
{
	struct mlx5_flow_steering *steering;
	int err = 0;

	err = mlx5_init_fc_stats(dev);
	if (err)
		return err;

	steering = kzalloc(sizeof(*steering), GFP_KERNEL);
	if (!steering)
		return -ENOMEM;
	steering->dev = dev;
	dev->priv.steering = steering;

	steering->fgs_cache = kmem_cache_create("mlx5_fs_fgs",
						sizeof(struct mlx5_flow_group), 0,
						0, NULL);
	steering->ftes_cache = kmem_cache_create("mlx5_fs_ftes", sizeof(struct fs_fte), 0,
						 0, NULL);
	if (!steering->ftes_cache || !steering->fgs_cache) {
		err = -ENOMEM;
		goto err;
	}

	if ((((MLX5_CAP_GEN(dev, port_type) == MLX5_CAP_PORT_TYPE_ETH) &&
	      (MLX5_CAP_GEN(dev, nic_flow_table))) ||
	     ((MLX5_CAP_GEN(dev, port_type) == MLX5_CAP_PORT_TYPE_IB) &&
	      MLX5_CAP_GEN(dev, ipoib_enhanced_offloads))) &&
	    MLX5_CAP_FLOWTABLE_NIC_RX(dev, ft_support)) {
		err = init_root_ns(steering);
		if (err)
			goto err;
	}

	if (MLX5_ESWITCH_MANAGER(dev)) {
		if (MLX5_CAP_ESW_FLOWTABLE_FDB(dev, ft_support)) {
			err = init_fdb_root_ns(steering);
			if (err)
				goto err;
		}
		if (MLX5_CAP_ESW_EGRESS_ACL(dev, ft_support)) {
			err = init_egress_acls_root_ns(dev);
			if (err)
				goto err;
		}
		if (MLX5_CAP_ESW_INGRESS_ACL(dev, ft_support)) {
			err = init_ingress_acls_root_ns(dev);
			if (err)
				goto err;
		}
	}

	if (MLX5_CAP_FLOWTABLE_SNIFFER_RX(dev, ft_support)) {
		err = init_sniffer_rx_root_ns(steering);
		if (err)
			goto err;
	}

	if (MLX5_CAP_FLOWTABLE_SNIFFER_TX(dev, ft_support)) {
		err = init_sniffer_tx_root_ns(steering);
		if (err)
			goto err;
	}

	if (MLX5_CAP_FLOWTABLE_RDMA_RX(dev, ft_support) &&
	    MLX5_CAP_FLOWTABLE_RDMA_RX(dev, table_miss_action_domain)) {
		err = init_rdma_rx_root_ns(steering);
		if (err)
			goto err;
	}

	if (MLX5_IPSEC_DEV(dev) || MLX5_CAP_FLOWTABLE_NIC_TX(dev, ft_support)) {
		err = init_egress_root_ns(steering);
		if (err)
			goto err;
	}

	return 0;
err:
	mlx5_cleanup_fs(dev);
	return err;
}