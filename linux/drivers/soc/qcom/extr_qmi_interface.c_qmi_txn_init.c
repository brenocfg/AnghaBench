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
struct qmi_txn {int id; void* dest; struct qmi_elem_info* ei; struct qmi_handle* qmi; int /*<<< orphan*/  completion; int /*<<< orphan*/  lock; } ;
struct qmi_handle {int /*<<< orphan*/  txn_lock; int /*<<< orphan*/  txns; } ;
struct qmi_elem_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  U16_MAX ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct qmi_txn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int qmi_txn_init(struct qmi_handle *qmi, struct qmi_txn *txn,
		 struct qmi_elem_info *ei, void *c_struct)
{
	int ret;

	memset(txn, 0, sizeof(*txn));

	mutex_init(&txn->lock);
	init_completion(&txn->completion);
	txn->qmi = qmi;
	txn->ei = ei;
	txn->dest = c_struct;

	mutex_lock(&qmi->txn_lock);
	ret = idr_alloc_cyclic(&qmi->txns, txn, 0, U16_MAX, GFP_KERNEL);
	if (ret < 0)
		pr_err("failed to allocate transaction id\n");

	txn->id = ret;
	mutex_unlock(&qmi->txn_lock);

	return ret;
}