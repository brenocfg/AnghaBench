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
struct TYPE_2__ {int exp_recovery; int /*<<< orphan*/  entry; int /*<<< orphan*/ * qedr_dev; } ;
struct qede_dev {TYPE_1__ rdma_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  _qede_rdma_dev_remove (struct qede_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qede_rdma_destroy_wq (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_rdma_supported (struct qede_dev*) ; 
 int /*<<< orphan*/  qedr_dev_list_lock ; 

void qede_rdma_dev_remove(struct qede_dev *edev, bool recovery)
{
	if (!qede_rdma_supported(edev))
		return;

	/* Cannot remove qedr while recovering since it wasn't fully stopped */
	if (!recovery) {
		qede_rdma_destroy_wq(edev);
		mutex_lock(&qedr_dev_list_lock);
		if (!edev->rdma_info.exp_recovery)
			_qede_rdma_dev_remove(edev);
		edev->rdma_info.qedr_dev = NULL;
		list_del(&edev->rdma_info.entry);
		mutex_unlock(&qedr_dev_list_lock);
	} else {
		if (!edev->rdma_info.exp_recovery) {
			mutex_lock(&qedr_dev_list_lock);
			_qede_rdma_dev_remove(edev);
			mutex_unlock(&qedr_dev_list_lock);
		}
		edev->rdma_info.exp_recovery = true;
	}
}