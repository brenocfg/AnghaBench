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
typedef  size_t u32 ;
struct megasas_instance {int max_fw_cmds; struct megasas_cmd** cmd_list; struct fusion_context* ctrl_context; } ;
struct megasas_cmd_fusion {size_t sync_cmd_idx; } ;
struct megasas_cmd {TYPE_2__* frame; scalar_t__ sync_cmd; } ;
struct fusion_context {struct megasas_cmd_fusion** cmd_list; } ;
struct TYPE_3__ {scalar_t__ cmd; int /*<<< orphan*/  cmd_status; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_OK ; 
 scalar_t__ MFI_CMD_ABORT ; 
 int /*<<< orphan*/  MFI_STAT_WRONG_STATE ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  megasas_complete_cmd (struct megasas_instance*,struct megasas_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void megasas_complete_outstanding_ioctls(struct megasas_instance *instance)
{
	int i;
	struct megasas_cmd *cmd_mfi;
	struct megasas_cmd_fusion *cmd_fusion;
	struct fusion_context *fusion = instance->ctrl_context;

	/* Find all outstanding ioctls */
	if (fusion) {
		for (i = 0; i < instance->max_fw_cmds; i++) {
			cmd_fusion = fusion->cmd_list[i];
			if (cmd_fusion->sync_cmd_idx != (u32)ULONG_MAX) {
				cmd_mfi = instance->cmd_list[cmd_fusion->sync_cmd_idx];
				if (cmd_mfi->sync_cmd &&
				    (cmd_mfi->frame->hdr.cmd != MFI_CMD_ABORT)) {
					cmd_mfi->frame->hdr.cmd_status =
							MFI_STAT_WRONG_STATE;
					megasas_complete_cmd(instance,
							     cmd_mfi, DID_OK);
				}
			}
		}
	} else {
		for (i = 0; i < instance->max_fw_cmds; i++) {
			cmd_mfi = instance->cmd_list[i];
			if (cmd_mfi->sync_cmd && cmd_mfi->frame->hdr.cmd !=
				MFI_CMD_ABORT)
				megasas_complete_cmd(instance, cmd_mfi, DID_OK);
		}
	}
}