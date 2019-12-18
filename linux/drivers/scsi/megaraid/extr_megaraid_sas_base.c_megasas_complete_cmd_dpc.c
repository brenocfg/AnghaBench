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
typedef  size_t u32 ;
struct megasas_instance {size_t max_fw_cmds; int /*<<< orphan*/  completion_lock; int /*<<< orphan*/ * consumer; struct megasas_cmd** cmd_list; TYPE_1__* pdev; int /*<<< orphan*/ * reply_queue; int /*<<< orphan*/ * producer; int /*<<< orphan*/  adprecovery; } ;
struct megasas_cmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DID_OK ; 
 scalar_t__ MEGASAS_HW_CRITICAL_ERROR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_check_and_restore_queue_depth (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_complete_cmd (struct megasas_instance*,struct megasas_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void megasas_complete_cmd_dpc(unsigned long instance_addr)
{
	u32 producer;
	u32 consumer;
	u32 context;
	struct megasas_cmd *cmd;
	struct megasas_instance *instance =
				(struct megasas_instance *)instance_addr;
	unsigned long flags;

	/* If we have already declared adapter dead, donot complete cmds */
	if (atomic_read(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR)
		return;

	spin_lock_irqsave(&instance->completion_lock, flags);

	producer = le32_to_cpu(*instance->producer);
	consumer = le32_to_cpu(*instance->consumer);

	while (consumer != producer) {
		context = le32_to_cpu(instance->reply_queue[consumer]);
		if (context >= instance->max_fw_cmds) {
			dev_err(&instance->pdev->dev, "Unexpected context value %x\n",
				context);
			BUG();
		}

		cmd = instance->cmd_list[context];

		megasas_complete_cmd(instance, cmd, DID_OK);

		consumer++;
		if (consumer == (instance->max_fw_cmds + 1)) {
			consumer = 0;
		}
	}

	*instance->consumer = cpu_to_le32(producer);

	spin_unlock_irqrestore(&instance->completion_lock, flags);

	/*
	 * Check if we can restore can_queue
	 */
	megasas_check_and_restore_queue_depth(instance);
}