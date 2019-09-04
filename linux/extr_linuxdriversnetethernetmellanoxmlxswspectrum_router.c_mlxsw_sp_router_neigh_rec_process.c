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
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
#define  MLXSW_REG_RAUHTD_TYPE_IPV4 129 
#define  MLXSW_REG_RAUHTD_TYPE_IPV6 128 
 int mlxsw_reg_rauhtd_rec_type_get (char*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_router_neigh_rec_ipv4_process (struct mlxsw_sp*,char*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_router_neigh_rec_ipv6_process (struct mlxsw_sp*,char*,int) ; 

__attribute__((used)) static void mlxsw_sp_router_neigh_rec_process(struct mlxsw_sp *mlxsw_sp,
					      char *rauhtd_pl, int rec_index)
{
	switch (mlxsw_reg_rauhtd_rec_type_get(rauhtd_pl, rec_index)) {
	case MLXSW_REG_RAUHTD_TYPE_IPV4:
		mlxsw_sp_router_neigh_rec_ipv4_process(mlxsw_sp, rauhtd_pl,
						       rec_index);
		break;
	case MLXSW_REG_RAUHTD_TYPE_IPV6:
		mlxsw_sp_router_neigh_rec_ipv6_process(mlxsw_sp, rauhtd_pl,
						       rec_index);
		break;
	}
}