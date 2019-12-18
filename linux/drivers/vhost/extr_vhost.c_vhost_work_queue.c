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
struct vhost_work {int /*<<< orphan*/  node; int /*<<< orphan*/  flags; } ;
struct vhost_dev {int /*<<< orphan*/  worker; int /*<<< orphan*/  work_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHOST_WORK_QUEUED ; 
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void vhost_work_queue(struct vhost_dev *dev, struct vhost_work *work)
{
	if (!dev->worker)
		return;

	if (!test_and_set_bit(VHOST_WORK_QUEUED, &work->flags)) {
		/* We can only add the work to the list after we're
		 * sure it was not in the list.
		 * test_and_set_bit() implies a memory barrier.
		 */
		llist_add(&work->node, &dev->work_list);
		wake_up_process(dev->worker);
	}
}