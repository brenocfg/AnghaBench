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
struct mlxsw_afa_block {int finished; int /*<<< orphan*/  cur_set; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLXSW_AFA_SET_GOTO_BINDING_CMD_NONE ; 
 int /*<<< orphan*/  mlxsw_afa_set_goto_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlxsw_afa_block_continue(struct mlxsw_afa_block *block)
{
	if (block->finished)
		return -EINVAL;
	mlxsw_afa_set_goto_set(block->cur_set,
			       MLXSW_AFA_SET_GOTO_BINDING_CMD_NONE, 0);
	block->finished = true;
	return 0;
}