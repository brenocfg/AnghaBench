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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_mcc_instruction { ____Placeholder_mlxsw_reg_mcc_instruction } mlxsw_reg_mcc_instruction ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mcc ; 
 int /*<<< orphan*/  mlxsw_reg_mcc_component_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcc_component_size_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcc_instruction_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mcc_update_handle_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_mcc_pack(char *payload,
				      enum mlxsw_reg_mcc_instruction instr,
				      u16 component_index, u32 update_handle,
				      u32 component_size)
{
	MLXSW_REG_ZERO(mcc, payload);
	mlxsw_reg_mcc_instruction_set(payload, instr);
	mlxsw_reg_mcc_component_index_set(payload, component_index);
	mlxsw_reg_mcc_update_handle_set(payload, update_handle);
	mlxsw_reg_mcc_component_size_set(payload, component_size);
}