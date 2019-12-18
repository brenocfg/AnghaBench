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
struct mlxsw_sp_nve_config {int /*<<< orphan*/  ul_sip; int /*<<< orphan*/  ul_proto; int /*<<< orphan*/  ul_tb_id; } ;
struct mlxsw_sp_nve {struct mlxsw_sp* mlxsw_sp; struct mlxsw_sp_nve_config config; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_nve_inc_parsing_depth_put (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp2_nve_vxlan_config_clear (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_router_nve_demote_decap (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp2_nve_vxlan_fini(struct mlxsw_sp_nve *nve)
{
	struct mlxsw_sp_nve_config *config = &nve->config;
	struct mlxsw_sp *mlxsw_sp = nve->mlxsw_sp;

	mlxsw_sp_router_nve_demote_decap(mlxsw_sp, config->ul_tb_id,
					 config->ul_proto, &config->ul_sip);
	mlxsw_sp2_nve_vxlan_config_clear(mlxsw_sp);
	__mlxsw_sp_nve_inc_parsing_depth_put(mlxsw_sp, 0);
}