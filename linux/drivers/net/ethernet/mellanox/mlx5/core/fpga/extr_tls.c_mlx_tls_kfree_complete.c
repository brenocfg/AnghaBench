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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_fpga_dma_buf {int dummy; } ;
struct mlx5_fpga_device {int dummy; } ;
struct mlx5_fpga_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_fpga_dma_buf*) ; 

__attribute__((used)) static void mlx_tls_kfree_complete(struct mlx5_fpga_conn *conn,
				   struct mlx5_fpga_device *fdev,
				   struct mlx5_fpga_dma_buf *buf, u8 status)
{
	kfree(buf);
}