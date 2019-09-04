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
struct esw_mc_addr {scalar_t__ uplink_rule; } ;
struct mlx5_eswitch {scalar_t__ mode; int enabled_vports; int total_vports; int /*<<< orphan*/  dev; struct esw_mc_addr mc_promisc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_IB ; 
 scalar_t__ SRIOV_LEGACY ; 
 scalar_t__ SRIOV_NONE ; 
 int SRIOV_OFFLOADS ; 
 int /*<<< orphan*/  esw_destroy_legacy_fdb_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_tsar (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_disable_vport (struct mlx5_eswitch*,int) ; 
 int /*<<< orphan*/  esw_info (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  esw_offloads_cleanup (struct mlx5_eswitch*,int) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (scalar_t__) ; 
 int /*<<< orphan*/  mlx5_reload_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5_eswitch_disable_sriov(struct mlx5_eswitch *esw)
{
	struct esw_mc_addr *mc_promisc;
	int old_mode;
	int nvports;
	int i;

	if (!ESW_ALLOWED(esw) || esw->mode == SRIOV_NONE)
		return;

	esw_info(esw->dev, "disable SRIOV: active vports(%d) mode(%d)\n",
		 esw->enabled_vports, esw->mode);

	mc_promisc = &esw->mc_promisc;
	nvports = esw->enabled_vports;

	for (i = 0; i < esw->total_vports; i++)
		esw_disable_vport(esw, i);

	if (mc_promisc && mc_promisc->uplink_rule)
		mlx5_del_flow_rules(mc_promisc->uplink_rule);

	esw_destroy_tsar(esw);

	if (esw->mode == SRIOV_LEGACY)
		esw_destroy_legacy_fdb_table(esw);
	else if (esw->mode == SRIOV_OFFLOADS)
		esw_offloads_cleanup(esw, nvports);

	old_mode = esw->mode;
	esw->mode = SRIOV_NONE;

	if (old_mode == SRIOV_OFFLOADS)
		mlx5_reload_interface(esw->dev, MLX5_INTERFACE_PROTOCOL_IB);
}