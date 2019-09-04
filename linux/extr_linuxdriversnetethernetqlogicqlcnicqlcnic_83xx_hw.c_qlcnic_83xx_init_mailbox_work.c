#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qlcnic_mailbox {int /*<<< orphan*/  status; int /*<<< orphan*/  work; int /*<<< orphan*/ * work_q; int /*<<< orphan*/  completion; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  aen_lock; int /*<<< orphan*/  queue_lock; struct qlcnic_adapter* adapter; int /*<<< orphan*/ * ops; } ;
struct qlcnic_hardware_context {struct qlcnic_mailbox* mailbox; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_MBX_READY ; 
 int /*<<< orphan*/ * create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qlcnic_mailbox*) ; 
 struct qlcnic_mailbox* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_mailbox_worker ; 
 int /*<<< orphan*/  qlcnic_83xx_mbx_ops ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int qlcnic_83xx_init_mailbox_work(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_mailbox *mbx;

	ahw->mailbox = kzalloc(sizeof(*mbx), GFP_KERNEL);
	if (!ahw->mailbox)
		return -ENOMEM;

	mbx = ahw->mailbox;
	mbx->ops = &qlcnic_83xx_mbx_ops;
	mbx->adapter = adapter;

	spin_lock_init(&mbx->queue_lock);
	spin_lock_init(&mbx->aen_lock);
	INIT_LIST_HEAD(&mbx->cmd_q);
	init_completion(&mbx->completion);

	mbx->work_q = create_singlethread_workqueue("qlcnic_mailbox");
	if (mbx->work_q == NULL) {
		kfree(mbx);
		return -ENOMEM;
	}

	INIT_WORK(&mbx->work, qlcnic_83xx_mailbox_worker);
	set_bit(QLC_83XX_MBX_READY, &mbx->status);
	return 0;
}