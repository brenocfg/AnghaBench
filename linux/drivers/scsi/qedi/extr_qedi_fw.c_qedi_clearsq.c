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
struct qedi_endpoint {int /*<<< orphan*/  handle; } ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  cdev; } ;
struct qedi_conn {int /*<<< orphan*/  iscsi_conn_id; scalar_t__ cmd_cleanup_cmpl; scalar_t__ cmd_cleanup_req; struct qedi_endpoint* ep; } ;
struct iscsi_task {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clear_sq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct qedi_conn*,struct qedi_endpoint*) ; 
 int /*<<< orphan*/  QEDI_LOG_INFO ; 
 int /*<<< orphan*/  QEDI_WARN (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int qedi_cleanup_all_io (struct qedi_ctx*,struct qedi_conn*,struct iscsi_task*,int) ; 
 TYPE_1__* qedi_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qedi_clearsq(struct qedi_ctx *qedi, struct qedi_conn *qedi_conn,
		  struct iscsi_task *task)
{
	struct qedi_endpoint *qedi_ep;
	int rval;

	qedi_ep = qedi_conn->ep;
	qedi_conn->cmd_cleanup_req = 0;
	qedi_conn->cmd_cleanup_cmpl = 0;

	if (!qedi_ep) {
		QEDI_WARN(&qedi->dbg_ctx,
			  "Cannot proceed, ep already disconnected, cid=0x%x\n",
			  qedi_conn->iscsi_conn_id);
		return;
	}

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "Clearing SQ for cid=0x%x, conn=%p, ep=%p\n",
		  qedi_conn->iscsi_conn_id, qedi_conn, qedi_ep);

	qedi_ops->clear_sq(qedi->cdev, qedi_ep->handle);

	rval = qedi_cleanup_all_io(qedi, qedi_conn, task, true);
	if (rval) {
		QEDI_ERR(&qedi->dbg_ctx,
			 "fatal error, need hard reset, cid=0x%x\n",
			 qedi_conn->iscsi_conn_id);
		WARN_ON(1);
	}
}