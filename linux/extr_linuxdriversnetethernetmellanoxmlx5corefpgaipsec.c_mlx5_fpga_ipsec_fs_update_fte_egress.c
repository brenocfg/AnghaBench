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
struct mlx5_flow_table {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
struct fs_fte {int dummy; } ;

/* Variables and functions */
 int fpga_ipsec_fs_update_fte (struct mlx5_core_dev*,struct mlx5_flow_table*,unsigned int,int,struct fs_fte*,int) ; 

__attribute__((used)) static int
mlx5_fpga_ipsec_fs_update_fte_egress(struct mlx5_core_dev *dev,
				     struct mlx5_flow_table *ft,
				     unsigned int group_id,
				     int modify_mask,
				     struct fs_fte *fte)
{
	return fpga_ipsec_fs_update_fte(dev, ft, group_id, modify_mask, fte,
					true);
}