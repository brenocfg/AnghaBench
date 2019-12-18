#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_fpga_query {scalar_t__ status; int /*<<< orphan*/  oper_image; int /*<<< orphan*/  admin_image; } ;
struct mlx5_fpga_device {int /*<<< orphan*/  last_oper_image; int /*<<< orphan*/  last_admin_image; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ MLX5_FPGA_STATUS_SUCCESS ; 
 int /*<<< orphan*/  mlx5_fpga_dbg (struct mlx5_fpga_device*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_err (struct mlx5_fpga_device*,char*,int,...) ; 
 int /*<<< orphan*/  mlx5_fpga_image_name (int /*<<< orphan*/ ) ; 
 int mlx5_fpga_query (int /*<<< orphan*/ ,struct mlx5_fpga_query*) ; 

__attribute__((used)) static int mlx5_fpga_device_load_check(struct mlx5_fpga_device *fdev)
{
	struct mlx5_fpga_query query;
	int err;

	err = mlx5_fpga_query(fdev->mdev, &query);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to query status: %d\n", err);
		return err;
	}

	fdev->last_admin_image = query.admin_image;
	fdev->last_oper_image = query.oper_image;

	mlx5_fpga_dbg(fdev, "Status %u; Admin image %u; Oper image %u\n",
		      query.status, query.admin_image, query.oper_image);

	if (query.status != MLX5_FPGA_STATUS_SUCCESS) {
		mlx5_fpga_err(fdev, "%s image failed to load; status %u\n",
			      mlx5_fpga_image_name(fdev->last_oper_image),
			      query.status);
		return -EIO;
	}

	return 0;
}