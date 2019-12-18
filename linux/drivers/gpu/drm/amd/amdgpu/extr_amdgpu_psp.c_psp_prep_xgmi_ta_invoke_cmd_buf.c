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
struct TYPE_3__ {void* ta_cmd_id; void* session_id; } ;
struct TYPE_4__ {TYPE_1__ cmd_invoke_cmd; } ;
struct psp_gfx_cmd_resp {TYPE_2__ cmd; int /*<<< orphan*/  cmd_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_CMD_ID_INVOKE_CMD ; 

__attribute__((used)) static void psp_prep_xgmi_ta_invoke_cmd_buf(struct psp_gfx_cmd_resp *cmd,
					    uint32_t ta_cmd_id,
					    uint32_t xgmi_session_id)
{
	cmd->cmd_id = GFX_CMD_ID_INVOKE_CMD;
	cmd->cmd.cmd_invoke_cmd.session_id = xgmi_session_id;
	cmd->cmd.cmd_invoke_cmd.ta_cmd_id = ta_cmd_id;
	/* Note: cmd_invoke_cmd.buf is not used for now */
}