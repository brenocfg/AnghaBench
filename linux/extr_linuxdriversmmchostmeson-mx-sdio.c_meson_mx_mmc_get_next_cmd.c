#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmc_command {scalar_t__ opcode; TYPE_1__* mrq; TYPE_2__* data; scalar_t__ error; } ;
struct TYPE_4__ {scalar_t__ error; } ;
struct TYPE_3__ {struct mmc_command* stop; int /*<<< orphan*/  sbc; struct mmc_command* cmd; } ;

/* Variables and functions */
 scalar_t__ MMC_SET_BLOCK_COUNT ; 
 scalar_t__ mmc_op_multi (scalar_t__) ; 

__attribute__((used)) static struct mmc_command *meson_mx_mmc_get_next_cmd(struct mmc_command *cmd)
{
	if (cmd->opcode == MMC_SET_BLOCK_COUNT && !cmd->error)
		return cmd->mrq->cmd;
	else if (mmc_op_multi(cmd->opcode) &&
		 (!cmd->mrq->sbc || cmd->error || cmd->data->error))
		return cmd->mrq->stop;
	else
		return NULL;
}