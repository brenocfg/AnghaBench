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
struct inode {int dummy; } ;
struct hidraw_list {int /*<<< orphan*/  node; int /*<<< orphan*/  read_mutex; struct hidraw* hidraw; } ;
struct hidraw {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  list; int /*<<< orphan*/  open; int /*<<< orphan*/  hid; int /*<<< orphan*/  exist; } ;
struct file {struct hidraw_list* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PM_HINT_FULLON ; 
 int /*<<< orphan*/  PM_HINT_NORMAL ; 
 int hid_hw_open (int /*<<< orphan*/ ) ; 
 int hid_hw_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hidraw** hidraw_table ; 
 unsigned int iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct hidraw_list*) ; 
 struct hidraw_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minors_lock ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hidraw_open(struct inode *inode, struct file *file)
{
	unsigned int minor = iminor(inode);
	struct hidraw *dev;
	struct hidraw_list *list;
	unsigned long flags;
	int err = 0;

	if (!(list = kzalloc(sizeof(struct hidraw_list), GFP_KERNEL))) {
		err = -ENOMEM;
		goto out;
	}

	mutex_lock(&minors_lock);
	if (!hidraw_table[minor] || !hidraw_table[minor]->exist) {
		err = -ENODEV;
		goto out_unlock;
	}

	dev = hidraw_table[minor];
	if (!dev->open++) {
		err = hid_hw_power(dev->hid, PM_HINT_FULLON);
		if (err < 0) {
			dev->open--;
			goto out_unlock;
		}

		err = hid_hw_open(dev->hid);
		if (err < 0) {
			hid_hw_power(dev->hid, PM_HINT_NORMAL);
			dev->open--;
			goto out_unlock;
		}
	}

	list->hidraw = hidraw_table[minor];
	mutex_init(&list->read_mutex);
	spin_lock_irqsave(&hidraw_table[minor]->list_lock, flags);
	list_add_tail(&list->node, &hidraw_table[minor]->list);
	spin_unlock_irqrestore(&hidraw_table[minor]->list_lock, flags);
	file->private_data = list;
out_unlock:
	mutex_unlock(&minors_lock);
out:
	if (err < 0)
		kfree(list);
	return err;

}