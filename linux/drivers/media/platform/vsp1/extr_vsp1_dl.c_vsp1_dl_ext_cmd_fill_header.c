#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vsp1_dl_ext_cmd {TYPE_1__* cmds; int /*<<< orphan*/  data_dma; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {scalar_t__ reserved; int /*<<< orphan*/  address_set; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */

__attribute__((used)) static void vsp1_dl_ext_cmd_fill_header(struct vsp1_dl_ext_cmd *cmd)
{
	cmd->cmds[0].opcode = cmd->opcode;
	cmd->cmds[0].flags = cmd->flags;
	cmd->cmds[0].address_set = cmd->data_dma;
	cmd->cmds[0].reserved = 0;
}