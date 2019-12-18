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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int mlxsw_cmd_exec (struct mlxsw_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mlxsw_cmd_exec_in(struct mlxsw_core *mlxsw_core, u16 opcode,
				    u8 opcode_mod, u32 in_mod, char *in_mbox,
				    size_t in_mbox_size)
{
	return mlxsw_cmd_exec(mlxsw_core, opcode, opcode_mod, in_mod, false,
			      false, in_mbox, in_mbox_size, NULL, 0);
}