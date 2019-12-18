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
struct inode {int dummy; } ;
struct hiddev_list {TYPE_1__* hiddev; int /*<<< orphan*/  node; } ;
struct file {struct hiddev_list* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  existancelock; int /*<<< orphan*/  hid; scalar_t__ exist; int /*<<< orphan*/  open; int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_HINT_NORMAL ; 
 int /*<<< orphan*/  hid_hw_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfree (struct hiddev_list*) ; 

__attribute__((used)) static int hiddev_release(struct inode * inode, struct file * file)
{
	struct hiddev_list *list = file->private_data;
	unsigned long flags;

	spin_lock_irqsave(&list->hiddev->list_lock, flags);
	list_del(&list->node);
	spin_unlock_irqrestore(&list->hiddev->list_lock, flags);

	mutex_lock(&list->hiddev->existancelock);
	if (!--list->hiddev->open) {
		if (list->hiddev->exist) {
			hid_hw_close(list->hiddev->hid);
			hid_hw_power(list->hiddev->hid, PM_HINT_NORMAL);
		} else {
			mutex_unlock(&list->hiddev->existancelock);
			kfree(list->hiddev);
			vfree(list);
			return 0;
		}
	}

	mutex_unlock(&list->hiddev->existancelock);
	vfree(list);

	return 0;
}