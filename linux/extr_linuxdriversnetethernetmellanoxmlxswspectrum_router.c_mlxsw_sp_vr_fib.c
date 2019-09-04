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
struct mlxsw_sp_vr {struct mlxsw_sp_fib* fib6; struct mlxsw_sp_fib* fib4; } ;
struct mlxsw_sp_fib {int dummy; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;

/* Variables and functions */
#define  MLXSW_SP_L3_PROTO_IPV4 129 
#define  MLXSW_SP_L3_PROTO_IPV6 128 

__attribute__((used)) static struct mlxsw_sp_fib *mlxsw_sp_vr_fib(const struct mlxsw_sp_vr *vr,
					    enum mlxsw_sp_l3proto proto)
{
	switch (proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		return vr->fib4;
	case MLXSW_SP_L3_PROTO_IPV6:
		return vr->fib6;
	}
	return NULL;
}