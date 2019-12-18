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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum mlxsw_reg_ralxx_protocol { ____Placeholder_mlxsw_reg_ralxx_protocol } mlxsw_reg_ralxx_protocol ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ralta_op_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ralta_protocol_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ralta_tree_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ralta ; 

__attribute__((used)) static inline void mlxsw_reg_ralta_pack(char *payload, bool alloc,
					enum mlxsw_reg_ralxx_protocol protocol,
					u8 tree_id)
{
	MLXSW_REG_ZERO(ralta, payload);
	mlxsw_reg_ralta_op_set(payload, !alloc);
	mlxsw_reg_ralta_protocol_set(payload, protocol);
	mlxsw_reg_ralta_tree_id_set(payload, tree_id);
}