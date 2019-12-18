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
struct qlcnic_mailbox {int /*<<< orphan*/  work_q; int /*<<< orphan*/  work; int /*<<< orphan*/  completion; int /*<<< orphan*/  status; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {struct qlcnic_mailbox* mailbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_83XX_MBX_READY ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_flush_mbx_queue (struct qlcnic_adapter*) ; 

void qlcnic_83xx_detach_mailbox_work(struct qlcnic_adapter *adapter)
{
	struct qlcnic_mailbox *mbx = adapter->ahw->mailbox;

	if (!mbx)
		return;

	clear_bit(QLC_83XX_MBX_READY, &mbx->status);
	complete(&mbx->completion);
	cancel_work_sync(&mbx->work);
	flush_workqueue(mbx->work_q);
	qlcnic_83xx_flush_mbx_queue(adapter);
}