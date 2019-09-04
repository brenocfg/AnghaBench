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
struct inode {scalar_t__ i_private; } ;
struct hid_device {int /*<<< orphan*/  debug_list_lock; int /*<<< orphan*/  debug_list; } ;
struct hid_debug_list {struct hid_device* hdev; int /*<<< orphan*/  node; int /*<<< orphan*/  read_mutex; int /*<<< orphan*/  hid_debug_fifo; } ;
struct file {struct hid_debug_list* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_DEBUG_FIFOSIZE ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hid_debug_list*) ; 
 struct hid_debug_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hid_debug_events_open(struct inode *inode, struct file *file)
{
	int err = 0;
	struct hid_debug_list *list;
	unsigned long flags;

	if (!(list = kzalloc(sizeof(struct hid_debug_list), GFP_KERNEL))) {
		err = -ENOMEM;
		goto out;
	}

	err = kfifo_alloc(&list->hid_debug_fifo, HID_DEBUG_FIFOSIZE, GFP_KERNEL);
	if (err) {
		kfree(list);
		goto out;
	}
	list->hdev = (struct hid_device *) inode->i_private;
	file->private_data = list;
	mutex_init(&list->read_mutex);

	spin_lock_irqsave(&list->hdev->debug_list_lock, flags);
	list_add_tail(&list->node, &list->hdev->debug_list);
	spin_unlock_irqrestore(&list->hdev->debug_list_lock, flags);

out:
	return err;
}