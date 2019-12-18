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
struct qrtr_ctrl_pkt {int dummy; } ;
struct qmi_ops {int dummy; } ;
struct qmi_msg_handler {int dummy; } ;
struct qmi_header {int dummy; } ;
struct qmi_handle {size_t recv_buf_size; int /*<<< orphan*/  recv_buf; int /*<<< orphan*/  wq; int /*<<< orphan*/  sock; int /*<<< orphan*/  sq; struct qmi_ops ops; struct qmi_msg_handler const* handlers; int /*<<< orphan*/  work; int /*<<< orphan*/  services; int /*<<< orphan*/  lookup_results; int /*<<< orphan*/  lookups; int /*<<< orphan*/  txns; int /*<<< orphan*/  sock_lock; int /*<<< orphan*/  txn_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  qmi_data_ready_work ; 
 int /*<<< orphan*/  qmi_sock_create (struct qmi_handle*,int /*<<< orphan*/ *) ; 

int qmi_handle_init(struct qmi_handle *qmi, size_t recv_buf_size,
		    const struct qmi_ops *ops,
		    const struct qmi_msg_handler *handlers)
{
	int ret;

	mutex_init(&qmi->txn_lock);
	mutex_init(&qmi->sock_lock);

	idr_init(&qmi->txns);

	INIT_LIST_HEAD(&qmi->lookups);
	INIT_LIST_HEAD(&qmi->lookup_results);
	INIT_LIST_HEAD(&qmi->services);

	INIT_WORK(&qmi->work, qmi_data_ready_work);

	qmi->handlers = handlers;
	if (ops)
		qmi->ops = *ops;

	/* Make room for the header */
	recv_buf_size += sizeof(struct qmi_header);
	/* Must also be sufficient to hold a control packet */
	if (recv_buf_size < sizeof(struct qrtr_ctrl_pkt))
		recv_buf_size = sizeof(struct qrtr_ctrl_pkt);

	qmi->recv_buf_size = recv_buf_size;
	qmi->recv_buf = kzalloc(recv_buf_size, GFP_KERNEL);
	if (!qmi->recv_buf)
		return -ENOMEM;

	qmi->wq = alloc_workqueue("qmi_msg_handler", WQ_UNBOUND, 1);
	if (!qmi->wq) {
		ret = -ENOMEM;
		goto err_free_recv_buf;
	}

	qmi->sock = qmi_sock_create(qmi, &qmi->sq);
	if (IS_ERR(qmi->sock)) {
		pr_err("failed to create QMI socket\n");
		ret = PTR_ERR(qmi->sock);
		goto err_destroy_wq;
	}

	return 0;

err_destroy_wq:
	destroy_workqueue(qmi->wq);
err_free_recv_buf:
	kfree(qmi->recv_buf);

	return ret;
}