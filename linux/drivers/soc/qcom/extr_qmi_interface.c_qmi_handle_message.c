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
typedef  int /*<<< orphan*/  tmp_txn ;
struct sockaddr_qrtr {int dummy; } ;
struct qmi_txn {int result; int /*<<< orphan*/  id; int /*<<< orphan*/  lock; int /*<<< orphan*/  completion; scalar_t__ dest; scalar_t__ ei; } ;
struct qmi_header {scalar_t__ type; int /*<<< orphan*/  txn_id; } ;
struct qmi_handle {int /*<<< orphan*/  txn_lock; int /*<<< orphan*/  txns; } ;

/* Variables and functions */
 scalar_t__ QMI_RESPONSE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct qmi_txn* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qmi_txn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int qmi_decode_message (void const*,size_t,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  qmi_invoke_handler (struct qmi_handle*,struct sockaddr_qrtr*,struct qmi_txn*,void const*,size_t) ; 

__attribute__((used)) static void qmi_handle_message(struct qmi_handle *qmi,
			       struct sockaddr_qrtr *sq,
			       const void *buf, size_t len)
{
	const struct qmi_header *hdr;
	struct qmi_txn tmp_txn;
	struct qmi_txn *txn = NULL;
	int ret;

	if (len < sizeof(*hdr)) {
		pr_err("ignoring short QMI packet\n");
		return;
	}

	hdr = buf;

	/* If this is a response, find the matching transaction handle */
	if (hdr->type == QMI_RESPONSE) {
		mutex_lock(&qmi->txn_lock);
		txn = idr_find(&qmi->txns, hdr->txn_id);

		/* Ignore unexpected responses */
		if (!txn) {
			mutex_unlock(&qmi->txn_lock);
			return;
		}

		mutex_lock(&txn->lock);
		mutex_unlock(&qmi->txn_lock);

		if (txn->dest && txn->ei) {
			ret = qmi_decode_message(buf, len, txn->ei, txn->dest);
			if (ret < 0)
				pr_err("failed to decode incoming message\n");

			txn->result = ret;
			complete(&txn->completion);
		} else  {
			qmi_invoke_handler(qmi, sq, txn, buf, len);
		}

		mutex_unlock(&txn->lock);
	} else {
		/* Create a txn based on the txn_id of the incoming message */
		memset(&tmp_txn, 0, sizeof(tmp_txn));
		tmp_txn.id = hdr->txn_id;

		qmi_invoke_handler(qmi, sq, &tmp_txn, buf, len);
	}
}