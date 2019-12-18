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
typedef  void* uint32_t ;
struct TYPE_3__ {void* reg_id; void* reg_value; } ;
struct TYPE_4__ {TYPE_1__ cmd_setup_reg_prog; } ;
struct psp_gfx_cmd_resp {TYPE_2__ cmd; int /*<<< orphan*/  cmd_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_CMD_ID_PROG_REG ; 

__attribute__((used)) static void psp_prep_reg_prog_cmd_buf(struct psp_gfx_cmd_resp *cmd,
		uint32_t id, uint32_t value)
{
	cmd->cmd_id = GFX_CMD_ID_PROG_REG;
	cmd->cmd.cmd_setup_reg_prog.reg_value = value;
	cmd->cmd.cmd_setup_reg_prog.reg_id = id;
}