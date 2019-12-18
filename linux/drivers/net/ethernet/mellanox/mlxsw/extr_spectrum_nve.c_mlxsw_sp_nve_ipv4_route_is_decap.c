#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ addr4; } ;
struct mlxsw_sp_nve_config {scalar_t__ ul_proto; scalar_t__ ul_tb_id; TYPE_1__ ul_sip; } ;
struct mlxsw_sp_nve {scalar_t__ num_nve_tunnels; struct mlxsw_sp_nve_config config; } ;
struct mlxsw_sp {struct mlxsw_sp_nve* nve; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ MLXSW_SP_L3_PROTO_IPV4 ; 

bool mlxsw_sp_nve_ipv4_route_is_decap(const struct mlxsw_sp *mlxsw_sp,
				      u32 tb_id, __be32 addr)
{
	struct mlxsw_sp_nve *nve = mlxsw_sp->nve;
	struct mlxsw_sp_nve_config *config = &nve->config;

	if (nve->num_nve_tunnels &&
	    config->ul_proto == MLXSW_SP_L3_PROTO_IPV4 &&
	    config->ul_sip.addr4 == addr && config->ul_tb_id == tb_id)
		return true;

	return false;
}