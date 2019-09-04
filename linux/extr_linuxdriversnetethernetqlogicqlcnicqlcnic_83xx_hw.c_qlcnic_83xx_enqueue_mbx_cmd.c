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
struct qlcnic_mailbox {unsigned long num_cmds; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  work; int /*<<< orphan*/  work_q; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  status; } ;
struct qlcnic_cmd_args {unsigned long total_cmds; int /*<<< orphan*/  list; int /*<<< orphan*/  rsp_opcode; int /*<<< orphan*/  completion; int /*<<< orphan*/  rsp_status; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {struct qlcnic_mailbox* mailbox; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  QLC_83XX_MBX_READY ; 
 int /*<<< orphan*/  QLC_83XX_MBX_RESPONSE_UNKNOWN ; 
 int /*<<< orphan*/  QLC_83XX_MBX_RESPONSE_WAIT ; 
 unsigned long QLC_83XX_MBX_TIMEOUT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_83xx_enqueue_mbx_cmd(struct qlcnic_adapter *adapter,
				       struct qlcnic_cmd_args *cmd,
				       unsigned long *timeout)
{
	struct qlcnic_mailbox *mbx = adapter->ahw->mailbox;

	if (test_bit(QLC_83XX_MBX_READY, &mbx->status)) {
		atomic_set(&cmd->rsp_status, QLC_83XX_MBX_RESPONSE_WAIT);
		init_completion(&cmd->completion);
		cmd->rsp_opcode = QLC_83XX_MBX_RESPONSE_UNKNOWN;

		spin_lock_bh(&mbx->queue_lock);

		list_add_tail(&cmd->list, &mbx->cmd_q);
		mbx->num_cmds++;
		cmd->total_cmds = mbx->num_cmds;
		*timeout = cmd->total_cmds * QLC_83XX_MBX_TIMEOUT;
		queue_work(mbx->work_q, &mbx->work);

		spin_unlock_bh(&mbx->queue_lock);

		return 0;
	}

	return -EBUSY;
}