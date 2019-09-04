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
typedef  enum mlxsw_reg_ralue_trap_action { ____Placeholder_mlxsw_reg_ralue_trap_action } mlxsw_reg_ralue_trap_action ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_RALUE_ACTION_TYPE_REMOTE ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_action_type_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_adjacency_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_ecmp_size_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_trap_action_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_trap_id_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlxsw_reg_ralue_act_remote_pack(char *payload,
				enum mlxsw_reg_ralue_trap_action trap_action,
				u16 trap_id, u32 adjacency_index, u16 ecmp_size)
{
	mlxsw_reg_ralue_action_type_set(payload,
					MLXSW_REG_RALUE_ACTION_TYPE_REMOTE);
	mlxsw_reg_ralue_trap_action_set(payload, trap_action);
	mlxsw_reg_ralue_trap_id_set(payload, trap_id);
	mlxsw_reg_ralue_adjacency_index_set(payload, adjacency_index);
	mlxsw_reg_ralue_ecmp_size_set(payload, ecmp_size);
}