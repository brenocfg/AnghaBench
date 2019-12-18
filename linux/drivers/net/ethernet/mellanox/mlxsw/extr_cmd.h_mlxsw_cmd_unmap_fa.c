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
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_CMD_OPCODE_UNMAP_FA ; 
 int mlxsw_cmd_exec_none (struct mlxsw_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mlxsw_cmd_unmap_fa(struct mlxsw_core *mlxsw_core)
{
	return mlxsw_cmd_exec_none(mlxsw_core, MLXSW_CMD_OPCODE_UNMAP_FA, 0, 0);
}