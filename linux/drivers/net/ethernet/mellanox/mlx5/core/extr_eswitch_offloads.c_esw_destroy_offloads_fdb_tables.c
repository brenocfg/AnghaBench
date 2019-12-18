#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ns; int /*<<< orphan*/  slow_fdb; int /*<<< orphan*/  miss_grp; int /*<<< orphan*/  peer_miss_grp; int /*<<< orphan*/  send_to_vport_grp; int /*<<< orphan*/  miss_rule_uni; int /*<<< orphan*/  miss_rule_multi; } ;
struct TYPE_4__ {TYPE_1__ offloads; } ;
struct mlx5_eswitch {TYPE_2__ fdb_table; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FLOW_STEERING_MODE_DMFS ; 
 int /*<<< orphan*/  esw_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esw_destroy_offloads_fast_fdb_tables (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_flow_namespace_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esw_destroy_offloads_fdb_tables(struct mlx5_eswitch *esw)
{
	if (!esw->fdb_table.offloads.slow_fdb)
		return;

	esw_debug(esw->dev, "Destroy offloads FDB Tables\n");
	mlx5_del_flow_rules(esw->fdb_table.offloads.miss_rule_multi);
	mlx5_del_flow_rules(esw->fdb_table.offloads.miss_rule_uni);
	mlx5_destroy_flow_group(esw->fdb_table.offloads.send_to_vport_grp);
	mlx5_destroy_flow_group(esw->fdb_table.offloads.peer_miss_grp);
	mlx5_destroy_flow_group(esw->fdb_table.offloads.miss_grp);

	mlx5_destroy_flow_table(esw->fdb_table.offloads.slow_fdb);
	esw_destroy_offloads_fast_fdb_tables(esw);
	/* Holds true only as long as DMFS is the default */
	mlx5_flow_namespace_set_mode(esw->fdb_table.offloads.ns,
				     MLX5_FLOW_STEERING_MODE_DMFS);
}