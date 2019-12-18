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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct cxgbit_device {int /*<<< orphan*/  list; TYPE_1__ cskq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_list_lock ; 
 int /*<<< orphan*/  cxgbit_close_conn (struct cxgbit_device*) ; 
 int /*<<< orphan*/  cxgbit_put_cdev (struct cxgbit_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxgbit_detach_cdev(struct cxgbit_device *cdev)
{
	bool free_cdev = false;

	spin_lock_bh(&cdev->cskq.lock);
	if (list_empty(&cdev->cskq.list))
		free_cdev = true;
	spin_unlock_bh(&cdev->cskq.lock);

	if (free_cdev) {
		mutex_lock(&cdev_list_lock);
		list_del(&cdev->list);
		mutex_unlock(&cdev_list_lock);

		cxgbit_put_cdev(cdev);
	} else {
		cxgbit_close_conn(cdev);
	}
}