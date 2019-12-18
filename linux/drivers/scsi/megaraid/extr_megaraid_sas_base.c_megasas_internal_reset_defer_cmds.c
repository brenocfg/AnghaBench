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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct megasas_instance {int max_fw_cmds; int /*<<< orphan*/  mfi_pool_lock; int /*<<< orphan*/  internal_reset_pending_q; TYPE_1__* pdev; struct megasas_cmd** cmd_list; } ;
struct megasas_cmd {int sync_cmd; int /*<<< orphan*/  list; int /*<<< orphan*/  scmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,struct megasas_cmd*,...) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
megasas_internal_reset_defer_cmds(struct megasas_instance *instance)
{
	struct megasas_cmd *cmd;
	int i;
	u16 max_cmd = instance->max_fw_cmds;
	u32 defer_index;
	unsigned long flags;

	defer_index = 0;
	spin_lock_irqsave(&instance->mfi_pool_lock, flags);
	for (i = 0; i < max_cmd; i++) {
		cmd = instance->cmd_list[i];
		if (cmd->sync_cmd == 1 || cmd->scmd) {
			dev_notice(&instance->pdev->dev, "moving cmd[%d]:%p:%d:%p"
					"on the defer queue as internal\n",
				defer_index, cmd, cmd->sync_cmd, cmd->scmd);

			if (!list_empty(&cmd->list)) {
				dev_notice(&instance->pdev->dev, "ERROR while"
					" moving this cmd:%p, %d %p, it was"
					"discovered on some list?\n",
					cmd, cmd->sync_cmd, cmd->scmd);

				list_del_init(&cmd->list);
			}
			defer_index++;
			list_add_tail(&cmd->list,
				&instance->internal_reset_pending_q);
		}
	}
	spin_unlock_irqrestore(&instance->mfi_pool_lock, flags);
}