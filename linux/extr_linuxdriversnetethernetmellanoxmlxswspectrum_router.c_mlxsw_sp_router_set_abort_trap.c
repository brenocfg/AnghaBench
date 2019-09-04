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
typedef  enum mlxsw_reg_ralxx_protocol { ____Placeholder_mlxsw_reg_ralxx_protocol } mlxsw_reg_ralxx_protocol ;

/* Variables and functions */
 int MLXSW_REG_RALXX_PROTOCOL_IPV4 ; 
 int MLXSW_REG_RALXX_PROTOCOL_IPV6 ; 
 scalar_t__ MLXSW_SP_LPM_TREE_MIN ; 
 int __mlxsw_sp_router_set_abort_trap (struct mlxsw_sp*,int,scalar_t__) ; 

__attribute__((used)) static int mlxsw_sp_router_set_abort_trap(struct mlxsw_sp *mlxsw_sp)
{
	enum mlxsw_reg_ralxx_protocol proto = MLXSW_REG_RALXX_PROTOCOL_IPV4;
	int err;

	err = __mlxsw_sp_router_set_abort_trap(mlxsw_sp, proto,
					       MLXSW_SP_LPM_TREE_MIN);
	if (err)
		return err;

	/* The multicast router code does not need an abort trap as by default,
	 * packets that don't match any routes are trapped to the CPU.
	 */

	proto = MLXSW_REG_RALXX_PROTOCOL_IPV6;
	return __mlxsw_sp_router_set_abort_trap(mlxsw_sp, proto,
						MLXSW_SP_LPM_TREE_MIN + 1);
}