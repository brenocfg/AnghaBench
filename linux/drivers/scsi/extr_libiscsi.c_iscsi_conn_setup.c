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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;
struct iscsi_session {TYPE_1__ cmdpool; int /*<<< orphan*/  frwd_lock; } ;
struct iscsi_conn {char* data; TYPE_2__* login_task; int /*<<< orphan*/  ehwait; int /*<<< orphan*/  tmf_timer; int /*<<< orphan*/  xmitwork; int /*<<< orphan*/  taskqueuelock; int /*<<< orphan*/  requeue; int /*<<< orphan*/  cmdqueue; int /*<<< orphan*/  mgmtqueue; int /*<<< orphan*/  transport_timer; int /*<<< orphan*/  tmf_state; scalar_t__ exp_statsn; int /*<<< orphan*/  id; int /*<<< orphan*/  c_stage; struct iscsi_cls_conn* cls_conn; struct iscsi_session* session; struct iscsi_conn* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct TYPE_4__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISCSI_CONN_INITIAL_STAGE ; 
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  TMF_INITIAL ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_check_transport_timeouts ; 
 struct iscsi_cls_conn* iscsi_create_conn (struct iscsi_cls_session*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_destroy_conn (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  iscsi_tmf_timedout ; 
 int /*<<< orphan*/  iscsi_xmitworker ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  kfifo_out (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  memset (struct iscsi_conn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct iscsi_cls_conn *
iscsi_conn_setup(struct iscsi_cls_session *cls_session, int dd_size,
		 uint32_t conn_idx)
{
	struct iscsi_session *session = cls_session->dd_data;
	struct iscsi_conn *conn;
	struct iscsi_cls_conn *cls_conn;
	char *data;

	cls_conn = iscsi_create_conn(cls_session, sizeof(*conn) + dd_size,
				     conn_idx);
	if (!cls_conn)
		return NULL;
	conn = cls_conn->dd_data;
	memset(conn, 0, sizeof(*conn) + dd_size);

	conn->dd_data = cls_conn->dd_data + sizeof(*conn);
	conn->session = session;
	conn->cls_conn = cls_conn;
	conn->c_stage = ISCSI_CONN_INITIAL_STAGE;
	conn->id = conn_idx;
	conn->exp_statsn = 0;
	conn->tmf_state = TMF_INITIAL;

	timer_setup(&conn->transport_timer, iscsi_check_transport_timeouts, 0);

	INIT_LIST_HEAD(&conn->mgmtqueue);
	INIT_LIST_HEAD(&conn->cmdqueue);
	INIT_LIST_HEAD(&conn->requeue);
	spin_lock_init(&conn->taskqueuelock);
	INIT_WORK(&conn->xmitwork, iscsi_xmitworker);

	/* allocate login_task used for the login/text sequences */
	spin_lock_bh(&session->frwd_lock);
	if (!kfifo_out(&session->cmdpool.queue,
                         (void*)&conn->login_task,
			 sizeof(void*))) {
		spin_unlock_bh(&session->frwd_lock);
		goto login_task_alloc_fail;
	}
	spin_unlock_bh(&session->frwd_lock);

	data = (char *) __get_free_pages(GFP_KERNEL,
					 get_order(ISCSI_DEF_MAX_RECV_SEG_LEN));
	if (!data)
		goto login_task_data_alloc_fail;
	conn->login_task->data = conn->data = data;

	timer_setup(&conn->tmf_timer, iscsi_tmf_timedout, 0);
	init_waitqueue_head(&conn->ehwait);

	return cls_conn;

login_task_data_alloc_fail:
	kfifo_in(&session->cmdpool.queue, (void*)&conn->login_task,
		    sizeof(void*));
login_task_alloc_fail:
	iscsi_destroy_conn(cls_conn);
	return NULL;
}