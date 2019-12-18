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
struct mlxsw_sp_nve_config {int /*<<< orphan*/  ul_sip; int /*<<< orphan*/  ul_proto; int /*<<< orphan*/  ul_tb_id; int /*<<< orphan*/  udp_dport; } ;
struct mlxsw_sp_nve {int /*<<< orphan*/  tunnel_index; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int __mlxsw_sp_nve_inc_parsing_depth_get (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mlxsw_sp_nve_inc_parsing_depth_put (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp1_nve_vxlan_config_clear (struct mlxsw_sp*) ; 
 int mlxsw_sp1_nve_vxlan_config_set (struct mlxsw_sp*,struct mlxsw_sp_nve_config const*) ; 
 int mlxsw_sp1_nve_vxlan_rtdp_set (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_router_nve_promote_decap (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp1_nve_vxlan_init(struct mlxsw_sp_nve *nve,
				    const struct mlxsw_sp_nve_config *config)
{
	struct mlxsw_sp *mlxsw_sp = nve->mlxsw_sp;
	int err;

	err = __mlxsw_sp_nve_inc_parsing_depth_get(mlxsw_sp, config->udp_dport);
	if (err)
		return err;

	err = mlxsw_sp1_nve_vxlan_config_set(mlxsw_sp, config);
	if (err)
		goto err_config_set;

	err = mlxsw_sp1_nve_vxlan_rtdp_set(mlxsw_sp, nve->tunnel_index);
	if (err)
		goto err_rtdp_set;

	err = mlxsw_sp_router_nve_promote_decap(mlxsw_sp, config->ul_tb_id,
						config->ul_proto,
						&config->ul_sip,
						nve->tunnel_index);
	if (err)
		goto err_promote_decap;

	return 0;

err_promote_decap:
err_rtdp_set:
	mlxsw_sp1_nve_vxlan_config_clear(mlxsw_sp);
err_config_set:
	__mlxsw_sp_nve_inc_parsing_depth_put(mlxsw_sp, 0);
	return err;
}