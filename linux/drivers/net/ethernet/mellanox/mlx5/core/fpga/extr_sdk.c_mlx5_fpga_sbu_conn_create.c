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
struct mlx5_fpga_device {int dummy; } ;
struct mlx5_fpga_conn_attr {int dummy; } ;
struct mlx5_fpga_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FPGA_QPC_QP_TYPE_SANDBOX_QP ; 
 struct mlx5_fpga_conn* mlx5_fpga_conn_create (struct mlx5_fpga_device*,struct mlx5_fpga_conn_attr*,int /*<<< orphan*/ ) ; 

struct mlx5_fpga_conn *
mlx5_fpga_sbu_conn_create(struct mlx5_fpga_device *fdev,
			  struct mlx5_fpga_conn_attr *attr)
{
	return mlx5_fpga_conn_create(fdev, attr, MLX5_FPGA_QPC_QP_TYPE_SANDBOX_QP);
}