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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_afa_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  MLXSW_AFA_TRAPDISC_CODE ; 
 int /*<<< orphan*/  MLXSW_AFA_TRAPDISC_FORWARD_ACTION_FORWARD ; 
 int /*<<< orphan*/  MLXSW_AFA_TRAPDISC_SIZE ; 
 int /*<<< orphan*/  MLXSW_AFA_TRAPDISC_TRAP_ACTION_TRAP ; 
 int PTR_ERR (char*) ; 
 char* mlxsw_afa_block_append_action (struct mlxsw_afa_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_trapdisc_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlxsw_afa_block_append_trap_and_forward(struct mlxsw_afa_block *block,
					    u16 trap_id)
{
	char *act = mlxsw_afa_block_append_action(block,
						  MLXSW_AFA_TRAPDISC_CODE,
						  MLXSW_AFA_TRAPDISC_SIZE);

	if (IS_ERR(act))
		return PTR_ERR(act);
	mlxsw_afa_trapdisc_pack(act, MLXSW_AFA_TRAPDISC_TRAP_ACTION_TRAP,
				MLXSW_AFA_TRAPDISC_FORWARD_ACTION_FORWARD,
				trap_id);
	return 0;
}