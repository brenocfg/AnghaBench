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
struct mlx5_flow_steering {int /*<<< orphan*/  fgs_cache; int /*<<< orphan*/  ftes_cache; int /*<<< orphan*/ * egress_root_ns; int /*<<< orphan*/ * rdma_rx_root_ns; int /*<<< orphan*/ * sniffer_tx_root_ns; int /*<<< orphan*/ * sniffer_rx_root_ns; struct mlx5_flow_steering* fdb_sub_ns; int /*<<< orphan*/ * fdb_root_ns; int /*<<< orphan*/ * root_ns; } ;
struct TYPE_2__ {struct mlx5_flow_steering* steering; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_egress_acls_root_ns (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  cleanup_ingress_acls_root_ns (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  cleanup_root_ns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_steering*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_cleanup_fc_stats (struct mlx5_core_dev*) ; 

void mlx5_cleanup_fs(struct mlx5_core_dev *dev)
{
	struct mlx5_flow_steering *steering = dev->priv.steering;

	cleanup_root_ns(steering->root_ns);
	cleanup_egress_acls_root_ns(dev);
	cleanup_ingress_acls_root_ns(dev);
	cleanup_root_ns(steering->fdb_root_ns);
	steering->fdb_root_ns = NULL;
	kfree(steering->fdb_sub_ns);
	steering->fdb_sub_ns = NULL;
	cleanup_root_ns(steering->sniffer_rx_root_ns);
	cleanup_root_ns(steering->sniffer_tx_root_ns);
	cleanup_root_ns(steering->rdma_rx_root_ns);
	cleanup_root_ns(steering->egress_root_ns);
	mlx5_cleanup_fc_stats(dev);
	kmem_cache_destroy(steering->ftes_cache);
	kmem_cache_destroy(steering->fgs_cache);
	kfree(steering);
}