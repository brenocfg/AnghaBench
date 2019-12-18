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
struct qede_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _qede_rdma_dev_close (struct qede_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qede_rdma_supported (struct qede_dev*) ; 
 int /*<<< orphan*/  qedr_dev_list_lock ; 

__attribute__((used)) static void qede_rdma_dev_close(struct qede_dev *edev)
{
	if (!qede_rdma_supported(edev))
		return;

	mutex_lock(&qedr_dev_list_lock);
	_qede_rdma_dev_close(edev);
	mutex_unlock(&qedr_dev_list_lock);
}