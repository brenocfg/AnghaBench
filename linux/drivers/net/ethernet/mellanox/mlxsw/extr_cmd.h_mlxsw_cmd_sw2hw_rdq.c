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
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_CMD_OPCODE_MOD_RDQ ; 
 int __mlxsw_cmd_sw2hw_dq (struct mlxsw_core*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mlxsw_cmd_sw2hw_rdq(struct mlxsw_core *mlxsw_core,
				      char *in_mbox, u32 dq_number)
{
	return __mlxsw_cmd_sw2hw_dq(mlxsw_core, in_mbox, dq_number,
				    MLXSW_CMD_OPCODE_MOD_RDQ);
}