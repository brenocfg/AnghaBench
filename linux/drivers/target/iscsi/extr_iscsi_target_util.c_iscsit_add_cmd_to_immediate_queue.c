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
typedef  int /*<<< orphan*/  u8 ;
struct iscsi_queue_req {int /*<<< orphan*/  qr_list; int /*<<< orphan*/  state; struct iscsi_cmd* cmd; } ;
struct iscsi_conn {int /*<<< orphan*/  queues_wq; int /*<<< orphan*/  immed_queue_lock; int /*<<< orphan*/  check_immediate_queue; int /*<<< orphan*/  immed_queue_list; } ;
struct iscsi_cmd {int /*<<< orphan*/  immed_queue_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct iscsi_queue_req* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_qr_cache ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void iscsit_add_cmd_to_immediate_queue(
	struct iscsi_cmd *cmd,
	struct iscsi_conn *conn,
	u8 state)
{
	struct iscsi_queue_req *qr;

	qr = kmem_cache_zalloc(lio_qr_cache, GFP_ATOMIC);
	if (!qr) {
		pr_err("Unable to allocate memory for"
				" struct iscsi_queue_req\n");
		return;
	}
	INIT_LIST_HEAD(&qr->qr_list);
	qr->cmd = cmd;
	qr->state = state;

	spin_lock_bh(&conn->immed_queue_lock);
	list_add_tail(&qr->qr_list, &conn->immed_queue_list);
	atomic_inc(&cmd->immed_queue_count);
	atomic_set(&conn->check_immediate_queue, 1);
	spin_unlock_bh(&conn->immed_queue_lock);

	wake_up(&conn->queues_wq);
}