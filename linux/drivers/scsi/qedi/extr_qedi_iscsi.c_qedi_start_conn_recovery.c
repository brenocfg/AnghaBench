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
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct qedi_conn {int abrt_conn; struct iscsi_cls_conn* cls_conn; int /*<<< orphan*/  iscsi_conn_id; } ;
struct iscsi_conn {TYPE_1__* session; } ;
struct iscsi_cls_session {int dummy; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_ERR_CONN_FAILED ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_failure (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 struct iscsi_cls_session* iscsi_conn_to_session (struct iscsi_cls_conn*) ; 
 scalar_t__ iscsi_is_session_online (struct iscsi_cls_session*) ; 

void qedi_start_conn_recovery(struct qedi_ctx *qedi,
			      struct qedi_conn *qedi_conn)
{
	struct iscsi_cls_session *cls_sess;
	struct iscsi_cls_conn *cls_conn;
	struct iscsi_conn *conn;

	cls_conn = qedi_conn->cls_conn;
	conn = cls_conn->dd_data;
	cls_sess = iscsi_conn_to_session(cls_conn);

	if (iscsi_is_session_online(cls_sess)) {
		qedi_conn->abrt_conn = 1;
		QEDI_ERR(&qedi->dbg_ctx,
			 "Failing connection, state=0x%x, cid=0x%x\n",
			 conn->session->state, qedi_conn->iscsi_conn_id);
		iscsi_conn_failure(qedi_conn->cls_conn->dd_data,
				   ISCSI_ERR_CONN_FAILED);
	}
}