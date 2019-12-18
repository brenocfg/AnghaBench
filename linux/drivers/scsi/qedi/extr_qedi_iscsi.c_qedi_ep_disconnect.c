#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qedi_endpoint {int state; size_t iscsi_cid; struct qedi_ctx* qedi; struct qedi_conn* conn; int /*<<< orphan*/  src_port; int /*<<< orphan*/  handle; int /*<<< orphan*/  tcp_ofld_wait; int /*<<< orphan*/  offload_work; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** conn_cid_tbl; } ;
struct qedi_ctx {int /*<<< orphan*/  num_offloads; int /*<<< orphan*/  lcl_port_tbl; TYPE_2__ cid_que; int /*<<< orphan*/ ** ep_tbl; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  cdev; int /*<<< orphan*/  flags; } ;
struct qedi_conn {int abrt_conn; int /*<<< orphan*/ * ep; int /*<<< orphan*/  active_cmd_count; int /*<<< orphan*/  flags; TYPE_1__* cls_conn; } ;
struct iscsi_endpoint {struct qedi_endpoint* dd_data; } ;
struct iscsi_conn {int dummy; } ;
struct TYPE_6__ {int (* destroy_conn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int (* release_conn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int DEF_MAX_RT_TIME ; 
 int EP_STATE_DISCONN_START ; 
 int EP_STATE_IDLE ; 
#define  EP_STATE_OFLDCONN_COMPL 131 
#define  EP_STATE_OFLDCONN_FAILED 130 
#define  EP_STATE_OFLDCONN_NONE 129 
#define  EP_STATE_OFLDCONN_START 128 
 int HZ ; 
 int /*<<< orphan*/  QEDI_CONN_FW_CLEANUP ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  QEDI_IN_RECOVERY ; 
 int /*<<< orphan*/  QEDI_LOG_INFO ; 
 int /*<<< orphan*/  QEDI_WARN (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_destroy_endpoint (struct iscsi_endpoint*) ; 
 int /*<<< orphan*/  iscsi_suspend_queue (struct iscsi_conn*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qedi_cleanup_active_cmd_list (struct qedi_conn*) ; 
 int /*<<< orphan*/  qedi_clearsq (struct qedi_ctx*,struct qedi_conn*,int /*<<< orphan*/ *) ; 
 scalar_t__ qedi_do_not_recover ; 
 int /*<<< orphan*/  qedi_free_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_free_sq (struct qedi_ctx*,struct qedi_endpoint*) ; 
 TYPE_3__* qedi_ops ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void qedi_ep_disconnect(struct iscsi_endpoint *ep)
{
	struct qedi_endpoint *qedi_ep;
	struct qedi_conn *qedi_conn = NULL;
	struct iscsi_conn *conn = NULL;
	struct qedi_ctx *qedi;
	int ret = 0;
	int wait_delay;
	int abrt_conn = 0;
	int count = 10;

	wait_delay = 60 * HZ + DEF_MAX_RT_TIME;
	qedi_ep = ep->dd_data;
	qedi = qedi_ep->qedi;

	if (qedi_ep->state == EP_STATE_OFLDCONN_START)
		goto ep_exit_recover;

	flush_work(&qedi_ep->offload_work);

	if (qedi_ep->conn) {
		qedi_conn = qedi_ep->conn;
		conn = qedi_conn->cls_conn->dd_data;
		iscsi_suspend_queue(conn);
		abrt_conn = qedi_conn->abrt_conn;

		while (count--)	{
			if (!test_bit(QEDI_CONN_FW_CLEANUP,
				      &qedi_conn->flags)) {
				break;
			}
			msleep(1000);
		}

		if (test_bit(QEDI_IN_RECOVERY, &qedi->flags)) {
			if (qedi_do_not_recover) {
				QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
					  "Do not recover cid=0x%x\n",
					  qedi_ep->iscsi_cid);
				goto ep_exit_recover;
			}
			QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
				  "Reset recovery cid=0x%x, qedi_ep=%p, state=0x%x\n",
				  qedi_ep->iscsi_cid, qedi_ep, qedi_ep->state);
			qedi_cleanup_active_cmd_list(qedi_conn);
			goto ep_release_conn;
		}
	}

	if (qedi_do_not_recover)
		goto ep_exit_recover;

	switch (qedi_ep->state) {
	case EP_STATE_OFLDCONN_START:
	case EP_STATE_OFLDCONN_NONE:
		goto ep_release_conn;
	case EP_STATE_OFLDCONN_FAILED:
			break;
	case EP_STATE_OFLDCONN_COMPL:
		if (unlikely(!qedi_conn))
			break;

		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
			  "Active cmd count=%d, abrt_conn=%d, ep state=0x%x, cid=0x%x, qedi_conn=%p\n",
			  qedi_conn->active_cmd_count, abrt_conn,
			  qedi_ep->state,
			  qedi_ep->iscsi_cid,
			  qedi_ep->conn
			  );

		if (!qedi_conn->active_cmd_count)
			abrt_conn = 0;
		else
			abrt_conn = 1;

		if (abrt_conn)
			qedi_clearsq(qedi, qedi_conn, NULL);
		break;
	default:
		break;
	}

	qedi_ep->state = EP_STATE_DISCONN_START;
	ret = qedi_ops->destroy_conn(qedi->cdev, qedi_ep->handle, abrt_conn);
	if (ret) {
		QEDI_WARN(&qedi->dbg_ctx,
			  "destroy_conn failed returned %d\n", ret);
	} else {
		ret = wait_event_interruptible_timeout(
					qedi_ep->tcp_ofld_wait,
					(qedi_ep->state !=
					 EP_STATE_DISCONN_START),
					wait_delay);
		if ((ret <= 0) || (qedi_ep->state == EP_STATE_DISCONN_START)) {
			QEDI_WARN(&qedi->dbg_ctx,
				  "Destroy conn timedout or interrupted, ret=%d, delay=%d, cid=0x%x\n",
				  ret, wait_delay, qedi_ep->iscsi_cid);
		}
	}

ep_release_conn:
	ret = qedi_ops->release_conn(qedi->cdev, qedi_ep->handle);
	if (ret)
		QEDI_WARN(&qedi->dbg_ctx,
			  "release_conn returned %d, cid=0x%x\n",
			  ret, qedi_ep->iscsi_cid);
ep_exit_recover:
	qedi_ep->state = EP_STATE_IDLE;
	qedi->ep_tbl[qedi_ep->iscsi_cid] = NULL;
	qedi->cid_que.conn_cid_tbl[qedi_ep->iscsi_cid] = NULL;
	qedi_free_id(&qedi->lcl_port_tbl, qedi_ep->src_port);
	qedi_free_sq(qedi, qedi_ep);

	if (qedi_conn)
		qedi_conn->ep = NULL;

	qedi_ep->conn = NULL;
	qedi_ep->qedi = NULL;
	atomic_dec(&qedi->num_offloads);

	iscsi_destroy_endpoint(ep);
}