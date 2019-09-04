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
struct TYPE_2__ {int /*<<< orphan*/  eswitch; } ;
struct mlx5_core_dev {int /*<<< orphan*/  vxlan; TYPE_1__ priv; int /*<<< orphan*/  tracer; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_cleanup_clock (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_mkey_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_qp_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_reserved_gids (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_rl_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_srq_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cq_debugfs_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_eq_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_eswitch_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_mpfs_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_sriov_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_vxlan_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_cleanup_once(struct mlx5_core_dev *dev)
{
	mlx5_fw_tracer_destroy(dev->tracer);
	mlx5_fpga_cleanup(dev);
	mlx5_sriov_cleanup(dev);
	mlx5_eswitch_cleanup(dev->priv.eswitch);
	mlx5_mpfs_cleanup(dev);
	mlx5_cleanup_rl_table(dev);
	mlx5_vxlan_destroy(dev->vxlan);
	mlx5_cleanup_clock(dev);
	mlx5_cleanup_reserved_gids(dev);
	mlx5_cleanup_mkey_table(dev);
	mlx5_cleanup_srq_table(dev);
	mlx5_cleanup_qp_table(dev);
	mlx5_cq_debugfs_cleanup(dev);
	mlx5_eq_cleanup(dev);
}