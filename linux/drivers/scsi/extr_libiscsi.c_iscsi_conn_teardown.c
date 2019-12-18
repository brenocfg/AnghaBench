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
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct iscsi_session {int /*<<< orphan*/  eh_mutex; int /*<<< orphan*/  frwd_lock; struct iscsi_conn* leadconn; int /*<<< orphan*/  back_lock; TYPE_1__ cmdpool; int /*<<< orphan*/  state; } ;
struct iscsi_conn {int /*<<< orphan*/  login_task; int /*<<< orphan*/  local_ipaddr; int /*<<< orphan*/  persistent_address; scalar_t__ data; int /*<<< orphan*/  ehwait; int /*<<< orphan*/  c_stage; int /*<<< orphan*/  transport_timer; struct iscsi_session* session; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_CONN_CLEANUP_WAIT ; 
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  ISCSI_STATE_TERMINATE ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_destroy_conn (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  iscsi_suspend_tx (struct iscsi_conn*) ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void iscsi_conn_teardown(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_session *session = conn->session;

	del_timer_sync(&conn->transport_timer);

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->frwd_lock);
	conn->c_stage = ISCSI_CONN_CLEANUP_WAIT;
	if (session->leadconn == conn) {
		/*
		 * leading connection? then give up on recovery.
		 */
		session->state = ISCSI_STATE_TERMINATE;
		wake_up(&conn->ehwait);
	}
	spin_unlock_bh(&session->frwd_lock);

	/* flush queued up work because we free the connection below */
	iscsi_suspend_tx(conn);

	spin_lock_bh(&session->frwd_lock);
	free_pages((unsigned long) conn->data,
		   get_order(ISCSI_DEF_MAX_RECV_SEG_LEN));
	kfree(conn->persistent_address);
	kfree(conn->local_ipaddr);
	/* regular RX path uses back_lock */
	spin_lock_bh(&session->back_lock);
	kfifo_in(&session->cmdpool.queue, (void*)&conn->login_task,
		    sizeof(void*));
	spin_unlock_bh(&session->back_lock);
	if (session->leadconn == conn)
		session->leadconn = NULL;
	spin_unlock_bh(&session->frwd_lock);
	mutex_unlock(&session->eh_mutex);

	iscsi_destroy_conn(cls_conn);
}