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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ MLXSW_REG_HTGT_INVALID_POLICER ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_PATH_TYPE_LOCAL ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_POLICER_DISABLE ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_POLICER_ENABLE ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_TRAP_TO_CPU ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htgt ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_local_path_cpu_tclass_set (char*,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_local_path_rdq_set (char*,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_mirror_action_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_mirroring_agent_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_pid_set (char*,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_pide_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_priority_set (char*,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_trap_group_set (char*,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_type_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_htgt_pack(char *payload, u8 group, u8 policer_id,
				       u8 priority, u8 tc)
{
	MLXSW_REG_ZERO(htgt, payload);

	if (policer_id == MLXSW_REG_HTGT_INVALID_POLICER) {
		mlxsw_reg_htgt_pide_set(payload,
					MLXSW_REG_HTGT_POLICER_DISABLE);
	} else {
		mlxsw_reg_htgt_pide_set(payload,
					MLXSW_REG_HTGT_POLICER_ENABLE);
		mlxsw_reg_htgt_pid_set(payload, policer_id);
	}

	mlxsw_reg_htgt_type_set(payload, MLXSW_REG_HTGT_PATH_TYPE_LOCAL);
	mlxsw_reg_htgt_trap_group_set(payload, group);
	mlxsw_reg_htgt_mirror_action_set(payload, MLXSW_REG_HTGT_TRAP_TO_CPU);
	mlxsw_reg_htgt_mirroring_agent_set(payload, 0);
	mlxsw_reg_htgt_priority_set(payload, priority);
	mlxsw_reg_htgt_local_path_cpu_tclass_set(payload, tc);
	mlxsw_reg_htgt_local_path_rdq_set(payload, group);
}