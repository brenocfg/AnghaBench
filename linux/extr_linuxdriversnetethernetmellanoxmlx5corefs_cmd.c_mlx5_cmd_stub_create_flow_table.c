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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum fs_flow_table_type { ____Placeholder_fs_flow_table_type } fs_flow_table_type ;
typedef  enum fs_flow_table_op_mod { ____Placeholder_fs_flow_table_op_mod } fs_flow_table_op_mod ;

/* Variables and functions */

__attribute__((used)) static int mlx5_cmd_stub_create_flow_table(struct mlx5_core_dev *dev,
					   u16 vport,
					   enum fs_flow_table_op_mod op_mod,
					   enum fs_flow_table_type type,
					   unsigned int level,
					   unsigned int log_size,
					   struct mlx5_flow_table *next_ft,
					   unsigned int *table_id, u32 flags)
{
	return 0;
}