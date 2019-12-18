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
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;
struct qede_dev {TYPE_1__ rdma_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _qede_rdma_dev_add (struct qede_dev*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qede_rdma_create_wq (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_rdma_supported (struct qede_dev*) ; 
 int /*<<< orphan*/  qedr_dev_list ; 
 int /*<<< orphan*/  qedr_dev_list_lock ; 

int qede_rdma_dev_add(struct qede_dev *edev, bool recovery)
{
	int rc;

	if (!qede_rdma_supported(edev))
		return 0;

	/* Cannot start qedr while recovering since it wasn't fully stopped */
	if (recovery)
		return 0;

	rc = qede_rdma_create_wq(edev);
	if (rc)
		return rc;

	INIT_LIST_HEAD(&edev->rdma_info.entry);
	mutex_lock(&qedr_dev_list_lock);
	list_add_tail(&edev->rdma_info.entry, &qedr_dev_list);
	_qede_rdma_dev_add(edev);
	mutex_unlock(&qedr_dev_list_lock);

	return rc;
}