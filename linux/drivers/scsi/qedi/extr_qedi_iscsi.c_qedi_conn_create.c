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
typedef  int /*<<< orphan*/  uint32_t ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct qedi_conn {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  active_cmd_list; scalar_t__ active_cmd_count; int /*<<< orphan*/ * ep; struct qedi_ctx* qedi; struct iscsi_cls_conn* cls_conn; } ;
struct iscsi_conn {struct qedi_conn* dd_data; } ;
struct iscsi_cls_session {int dummy; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ALERT ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*,int /*<<< orphan*/ ,struct iscsi_cls_session*) ; 
 struct iscsi_cls_conn* iscsi_conn_setup (struct iscsi_cls_session*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_teardown (struct iscsi_cls_conn*) ; 
 struct qedi_ctx* iscsi_host_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* iscsi_session_to_shost (struct iscsi_cls_session*) ; 
 scalar_t__ qedi_conn_alloc_login_resources (struct qedi_ctx*,struct qedi_conn*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iscsi_cls_conn *
qedi_conn_create(struct iscsi_cls_session *cls_session, uint32_t cid)
{
	struct Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	struct qedi_ctx *qedi = iscsi_host_priv(shost);
	struct iscsi_cls_conn *cls_conn;
	struct qedi_conn *qedi_conn;
	struct iscsi_conn *conn;

	cls_conn = iscsi_conn_setup(cls_session, sizeof(*qedi_conn),
				    cid);
	if (!cls_conn) {
		QEDI_ERR(&qedi->dbg_ctx,
			 "conn_new: iscsi conn setup failed, cid=0x%x, cls_sess=%p!\n",
			 cid, cls_session);
		return NULL;
	}

	conn = cls_conn->dd_data;
	qedi_conn = conn->dd_data;
	qedi_conn->cls_conn = cls_conn;
	qedi_conn->qedi = qedi;
	qedi_conn->ep = NULL;
	qedi_conn->active_cmd_count = 0;
	INIT_LIST_HEAD(&qedi_conn->active_cmd_list);
	spin_lock_init(&qedi_conn->list_lock);

	if (qedi_conn_alloc_login_resources(qedi, qedi_conn)) {
		iscsi_conn_printk(KERN_ALERT, conn,
				  "conn_new: login resc alloc failed, cid=0x%x, cls_sess=%p!!\n",
				   cid, cls_session);
		goto free_conn;
	}

	return cls_conn;

free_conn:
	iscsi_conn_teardown(cls_conn);
	return NULL;
}