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
struct qedi_ctx {int dummy; } ;
struct qedi_conn {scalar_t__ abrt_conn; int /*<<< orphan*/  flags; struct qedi_ctx* qedi; } ;
struct iscsi_conn {struct qedi_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ALERT ; 
 int /*<<< orphan*/  QEDI_CONN_FW_CLEANUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*) ; 
 int iscsi_conn_start (struct iscsi_cls_conn*) ; 
 int qedi_iscsi_update_conn (struct qedi_ctx*,struct qedi_conn*) ; 

__attribute__((used)) static int qedi_conn_start(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct qedi_conn *qedi_conn = conn->dd_data;
	struct qedi_ctx *qedi;
	int rval;

	qedi = qedi_conn->qedi;

	rval = qedi_iscsi_update_conn(qedi, qedi_conn);
	if (rval) {
		iscsi_conn_printk(KERN_ALERT, conn,
				  "conn_start: FW offload conn failed.\n");
		rval = -EINVAL;
		goto start_err;
	}

	clear_bit(QEDI_CONN_FW_CLEANUP, &qedi_conn->flags);
	qedi_conn->abrt_conn = 0;

	rval = iscsi_conn_start(cls_conn);
	if (rval) {
		iscsi_conn_printk(KERN_ALERT, conn,
				  "iscsi_conn_start: FW offload conn failed!!\n");
	}

start_err:
	return rval;
}