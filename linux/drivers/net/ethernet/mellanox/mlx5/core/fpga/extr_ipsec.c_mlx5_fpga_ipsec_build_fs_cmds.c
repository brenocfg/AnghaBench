#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  update_root_ft; int /*<<< orphan*/  delete_fte; int /*<<< orphan*/  update_fte; int /*<<< orphan*/  create_fte; int /*<<< orphan*/  destroy_flow_group; int /*<<< orphan*/  create_flow_group; int /*<<< orphan*/  modify_flow_table; int /*<<< orphan*/  destroy_flow_table; int /*<<< orphan*/  create_flow_table; } ;
struct TYPE_5__ {int /*<<< orphan*/  update_root_ft; int /*<<< orphan*/  delete_fte; int /*<<< orphan*/  update_fte; int /*<<< orphan*/  create_fte; int /*<<< orphan*/  destroy_flow_group; int /*<<< orphan*/  create_flow_group; int /*<<< orphan*/  modify_flow_table; int /*<<< orphan*/  destroy_flow_table; int /*<<< orphan*/  create_flow_table; } ;
struct TYPE_4__ {int /*<<< orphan*/  update_root_ft; int /*<<< orphan*/  destroy_flow_group; int /*<<< orphan*/  modify_flow_table; int /*<<< orphan*/  destroy_flow_table; int /*<<< orphan*/  create_flow_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  egress_to_fs_ft (int) ; 
 TYPE_3__ fpga_ipsec_egress ; 
 TYPE_2__ fpga_ipsec_ingress ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_fs_create_flow_group_egress ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_fs_create_flow_group_ingress ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_fs_create_fte_egress ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_fs_create_fte_ingress ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_fs_delete_fte_egress ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_fs_delete_fte_ingress ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_fs_update_fte_egress ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_fs_update_fte_ingress ; 
 TYPE_1__* mlx5_fs_cmd_get_default (int /*<<< orphan*/ ) ; 

void mlx5_fpga_ipsec_build_fs_cmds(void)
{
	/* ingress */
	fpga_ipsec_ingress.create_flow_table =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(false))->create_flow_table;
	fpga_ipsec_ingress.destroy_flow_table =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(false))->destroy_flow_table;
	fpga_ipsec_ingress.modify_flow_table =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(false))->modify_flow_table;
	fpga_ipsec_ingress.create_flow_group =
		mlx5_fpga_ipsec_fs_create_flow_group_ingress;
	fpga_ipsec_ingress.destroy_flow_group =
		 mlx5_fs_cmd_get_default(egress_to_fs_ft(false))->destroy_flow_group;
	fpga_ipsec_ingress.create_fte =
		mlx5_fpga_ipsec_fs_create_fte_ingress;
	fpga_ipsec_ingress.update_fte =
		mlx5_fpga_ipsec_fs_update_fte_ingress;
	fpga_ipsec_ingress.delete_fte =
		mlx5_fpga_ipsec_fs_delete_fte_ingress;
	fpga_ipsec_ingress.update_root_ft =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(false))->update_root_ft;

	/* egress */
	fpga_ipsec_egress.create_flow_table =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(true))->create_flow_table;
	fpga_ipsec_egress.destroy_flow_table =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(true))->destroy_flow_table;
	fpga_ipsec_egress.modify_flow_table =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(true))->modify_flow_table;
	fpga_ipsec_egress.create_flow_group =
		mlx5_fpga_ipsec_fs_create_flow_group_egress;
	fpga_ipsec_egress.destroy_flow_group =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(true))->destroy_flow_group;
	fpga_ipsec_egress.create_fte =
		mlx5_fpga_ipsec_fs_create_fte_egress;
	fpga_ipsec_egress.update_fte =
		mlx5_fpga_ipsec_fs_update_fte_egress;
	fpga_ipsec_egress.delete_fte =
		mlx5_fpga_ipsec_fs_delete_fte_egress;
	fpga_ipsec_egress.update_root_ft =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(true))->update_root_ft;
}