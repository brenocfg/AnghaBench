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
struct qlcnic_mailbox {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  num_cmds; } ;
struct qlcnic_cmd_args {int /*<<< orphan*/  list; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {struct qlcnic_mailbox* mailbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_83xx_notify_cmd_completion (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_83xx_dequeue_mbx_cmd(struct qlcnic_adapter *adapter,
					struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_mailbox *mbx = adapter->ahw->mailbox;

	spin_lock_bh(&mbx->queue_lock);

	list_del(&cmd->list);
	mbx->num_cmds--;

	spin_unlock_bh(&mbx->queue_lock);

	qlcnic_83xx_notify_cmd_completion(adapter, cmd);
}