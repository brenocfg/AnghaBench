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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_CMD_OPCODE_HW2SW_DQ ; 
 int mlxsw_cmd_exec_none (struct mlxsw_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __mlxsw_cmd_hw2sw_dq(struct mlxsw_core *mlxsw_core,
				       u32 dq_number, u8 opcode_mod)
{
	return mlxsw_cmd_exec_none(mlxsw_core, MLXSW_CMD_OPCODE_HW2SW_DQ,
				   opcode_mod, dq_number);
}