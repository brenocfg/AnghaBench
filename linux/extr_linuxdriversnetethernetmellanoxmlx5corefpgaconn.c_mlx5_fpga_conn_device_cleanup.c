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
struct TYPE_2__ {int /*<<< orphan*/  uar; int /*<<< orphan*/  pdn; int /*<<< orphan*/  mkey; } ;
struct mlx5_fpga_device {int /*<<< orphan*/  mdev; TYPE_1__ conn_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_dealloc_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_mkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_nic_vport_disable_roce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_put_uars_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5_fpga_conn_device_cleanup(struct mlx5_fpga_device *fdev)
{
	mlx5_core_destroy_mkey(fdev->mdev, &fdev->conn_res.mkey);
	mlx5_core_dealloc_pd(fdev->mdev, fdev->conn_res.pdn);
	mlx5_put_uars_page(fdev->mdev, fdev->conn_res.uar);
	mlx5_nic_vport_disable_roce(fdev->mdev);
}