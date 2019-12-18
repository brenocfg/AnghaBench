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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  session_id; } ;
struct TYPE_4__ {TYPE_1__ cmd_unload_ta; } ;
struct psp_gfx_cmd_resp {TYPE_2__ cmd; int /*<<< orphan*/  cmd_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_CMD_ID_UNLOAD_TA ; 

__attribute__((used)) static void psp_prep_ras_ta_unload_cmd_buf(struct psp_gfx_cmd_resp *cmd,
						uint32_t ras_session_id)
{
	cmd->cmd_id = GFX_CMD_ID_UNLOAD_TA;
	cmd->cmd.cmd_unload_ta.session_id = ras_session_id;
}