#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct hidraw_list {int /*<<< orphan*/  node; } ;
struct file {struct hidraw_list* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  drop_ref (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__** hidraw_table ; 
 unsigned int iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct hidraw_list*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minors_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hidraw_release(struct inode * inode, struct file * file)
{
	unsigned int minor = iminor(inode);
	struct hidraw_list *list = file->private_data;
	unsigned long flags;

	mutex_lock(&minors_lock);

	spin_lock_irqsave(&hidraw_table[minor]->list_lock, flags);
	list_del(&list->node);
	spin_unlock_irqrestore(&hidraw_table[minor]->list_lock, flags);
	kfree(list);

	drop_ref(hidraw_table[minor], 0);

	mutex_unlock(&minors_lock);
	return 0;
}