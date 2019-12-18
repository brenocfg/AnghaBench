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
struct mlx5dr_fw_recalc_cs_ft {int /*<<< orphan*/  table_id; int /*<<< orphan*/  group_id; int /*<<< orphan*/  modify_hdr_id; } ;
struct mlx5dr_domain {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FLOW_TABLE_TYPE_FDB ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_fw_recalc_cs_ft*) ; 
 int /*<<< orphan*/  mlx5dr_cmd_dealloc_modify_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_cmd_del_flow_table_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_cmd_destroy_flow_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_cmd_destroy_flow_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5dr_fw_destroy_recalc_cs_ft(struct mlx5dr_domain *dmn,
				    struct mlx5dr_fw_recalc_cs_ft *recalc_cs_ft)
{
	mlx5dr_cmd_del_flow_table_entry(dmn->mdev,
					MLX5_FLOW_TABLE_TYPE_FDB,
					recalc_cs_ft->table_id);
	mlx5dr_cmd_dealloc_modify_header(dmn->mdev, recalc_cs_ft->modify_hdr_id);
	mlx5dr_cmd_destroy_flow_group(dmn->mdev,
				      MLX5_FLOW_TABLE_TYPE_FDB,
				      recalc_cs_ft->table_id,
				      recalc_cs_ft->group_id);
	mlx5dr_cmd_destroy_flow_table(dmn->mdev,
				      recalc_cs_ft->table_id,
				      MLX5_FLOW_TABLE_TYPE_FDB);

	kfree(recalc_cs_ft);
}