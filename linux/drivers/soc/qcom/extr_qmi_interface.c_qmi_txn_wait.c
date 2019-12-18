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
struct qmi_txn {int result; int /*<<< orphan*/  lock; int /*<<< orphan*/  id; int /*<<< orphan*/  completion; struct qmi_handle* qmi; } ;
struct qmi_handle {int /*<<< orphan*/  txn_lock; int /*<<< orphan*/  txns; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

int qmi_txn_wait(struct qmi_txn *txn, unsigned long timeout)
{
	struct qmi_handle *qmi = txn->qmi;
	int ret;

	ret = wait_for_completion_timeout(&txn->completion, timeout);

	mutex_lock(&qmi->txn_lock);
	mutex_lock(&txn->lock);
	idr_remove(&qmi->txns, txn->id);
	mutex_unlock(&txn->lock);
	mutex_unlock(&qmi->txn_lock);

	if (ret == 0)
		return -ETIMEDOUT;
	else
		return txn->result;
}