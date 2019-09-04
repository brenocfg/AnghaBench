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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum mlxsw_reg_mgpc_opcode { ____Placeholder_mlxsw_reg_mgpc_opcode } mlxsw_reg_mgpc_opcode ;
typedef  enum mlxsw_reg_flow_counter_set_type { ____Placeholder_mlxsw_reg_flow_counter_set_type } mlxsw_reg_flow_counter_set_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mgpc ; 
 int /*<<< orphan*/  mlxsw_reg_mgpc_counter_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mgpc_counter_set_type_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mgpc_opcode_set (char*,int) ; 

__attribute__((used)) static inline void mlxsw_reg_mgpc_pack(char *payload, u32 counter_index,
				       enum mlxsw_reg_mgpc_opcode opcode,
				       enum mlxsw_reg_flow_counter_set_type set_type)
{
	MLXSW_REG_ZERO(mgpc, payload);
	mlxsw_reg_mgpc_counter_index_set(payload, counter_index);
	mlxsw_reg_mgpc_counter_set_type_set(payload, set_type);
	mlxsw_reg_mgpc_opcode_set(payload, opcode);
}