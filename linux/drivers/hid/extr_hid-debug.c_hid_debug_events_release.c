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
struct hid_debug_list {int /*<<< orphan*/  hid_debug_fifo; TYPE_1__* hdev; int /*<<< orphan*/  node; } ;
struct file {struct hid_debug_list* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  debug_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hid_debug_list*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hid_debug_events_release(struct inode *inode, struct file *file)
{
	struct hid_debug_list *list = file->private_data;
	unsigned long flags;

	spin_lock_irqsave(&list->hdev->debug_list_lock, flags);
	list_del(&list->node);
	spin_unlock_irqrestore(&list->hdev->debug_list_lock, flags);
	kfifo_free(&list->hid_debug_fifo);
	kfree(list);

	return 0;
}