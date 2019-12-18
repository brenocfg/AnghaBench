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
typedef  scalar_t__ u32 ;
struct qedi_endpoint {struct qedi_ctx* qedi; struct qedi_conn* conn; } ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct qedi_conn {int /*<<< orphan*/  qedi; TYPE_1__* cls_conn; } ;
struct iscsi_eqe_data {int /*<<< orphan*/  error_code; } ;
struct TYPE_2__ {int /*<<< orphan*/  dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ALERT ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* qedi_get_iscsi_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_start_conn_recovery (int /*<<< orphan*/ ,struct qedi_conn*) ; 

void qedi_process_iscsi_error(struct qedi_endpoint *ep,
			      struct iscsi_eqe_data *data)
{
	struct qedi_conn *qedi_conn;
	struct qedi_ctx *qedi;
	char warn_notice[] = "iscsi_warning";
	char error_notice[] = "iscsi_error";
	char unknown_msg[] = "Unknown error";
	char *message;
	int need_recovery = 0;
	u32 err_mask = 0;
	char *msg;

	if (!ep)
		return;

	qedi_conn = ep->conn;
	if (!qedi_conn)
		return;

	qedi = ep->qedi;

	QEDI_ERR(&qedi->dbg_ctx, "async event iscsi error:0x%x\n",
		 data->error_code);

	if (err_mask) {
		need_recovery = 0;
		message = warn_notice;
	} else {
		need_recovery = 1;
		message = error_notice;
	}

	msg = qedi_get_iscsi_error(data->error_code);
	if (!msg) {
		need_recovery = 0;
		msg = unknown_msg;
	}

	iscsi_conn_printk(KERN_ALERT,
			  qedi_conn->cls_conn->dd_data,
			  "qedi: %s - %s\n", message, msg);

	if (need_recovery)
		qedi_start_conn_recovery(qedi_conn->qedi, qedi_conn);
}