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
struct TYPE_2__ {int /*<<< orphan*/  uar; } ;
struct mlx5_core_dev {TYPE_1__ priv; int /*<<< orphan*/  tracer; int /*<<< orphan*/  hv_vhca; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_accel_ipsec_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_accel_tls_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_fs (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_ec_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_eq_table_destroy (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_events_stop (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fpga_device_stop (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_hv_vhca_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_irq_table_destroy (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pagealloc_stop (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_put_uars_page (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_sriov_detach (struct mlx5_core_dev*) ; 

__attribute__((used)) static void mlx5_unload(struct mlx5_core_dev *dev)
{
	mlx5_ec_cleanup(dev);
	mlx5_sriov_detach(dev);
	mlx5_cleanup_fs(dev);
	mlx5_accel_ipsec_cleanup(dev);
	mlx5_accel_tls_cleanup(dev);
	mlx5_fpga_device_stop(dev);
	mlx5_hv_vhca_cleanup(dev->hv_vhca);
	mlx5_fw_tracer_cleanup(dev->tracer);
	mlx5_eq_table_destroy(dev);
	mlx5_irq_table_destroy(dev);
	mlx5_pagealloc_stop(dev);
	mlx5_events_stop(dev);
	mlx5_put_uars_page(dev, dev->priv.uar);
}