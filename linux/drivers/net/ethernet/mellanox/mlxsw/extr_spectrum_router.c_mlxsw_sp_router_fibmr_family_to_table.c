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
struct mlxsw_sp_vr {struct mlxsw_sp_mr_table** mr_table; } ;
struct mlxsw_sp_mr_table {int dummy; } ;

/* Variables and functions */
 size_t MLXSW_SP_L3_PROTO_IPV4 ; 
 size_t MLXSW_SP_L3_PROTO_IPV6 ; 
 int RTNL_FAMILY_IPMR ; 

__attribute__((used)) static struct mlxsw_sp_mr_table *
mlxsw_sp_router_fibmr_family_to_table(struct mlxsw_sp_vr *vr, int family)
{
	if (family == RTNL_FAMILY_IPMR)
		return vr->mr_table[MLXSW_SP_L3_PROTO_IPV4];
	else
		return vr->mr_table[MLXSW_SP_L3_PROTO_IPV6];
}