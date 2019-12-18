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
struct smu_cmd {scalar_t__ data_len; scalar_t__ reply_len; int status; int /*<<< orphan*/  link; } ;
struct TYPE_2__ {int /*<<< orphan*/  db_irq; int /*<<< orphan*/  lock; int /*<<< orphan*/ * cmd_cur; int /*<<< orphan*/  cmd_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ SMU_MAX_DATA ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* smu ; 
 int /*<<< orphan*/  smu_irq_inited ; 
 int /*<<< orphan*/  smu_spinwait_cmd (struct smu_cmd*) ; 
 int /*<<< orphan*/  smu_start_cmd () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int smu_queue_cmd(struct smu_cmd *cmd)
{
	unsigned long flags;

	if (smu == NULL)
		return -ENODEV;
	if (cmd->data_len > SMU_MAX_DATA ||
	    cmd->reply_len > SMU_MAX_DATA)
		return -EINVAL;

	cmd->status = 1;
	spin_lock_irqsave(&smu->lock, flags);
	list_add_tail(&cmd->link, &smu->cmd_list);
	if (smu->cmd_cur == NULL)
		smu_start_cmd();
	spin_unlock_irqrestore(&smu->lock, flags);

	/* Workaround for early calls when irq isn't available */
	if (!smu_irq_inited || !smu->db_irq)
		smu_spinwait_cmd(cmd);

	return 0;
}