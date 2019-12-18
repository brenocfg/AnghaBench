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
struct inode {struct dev_data* i_private; } ;
struct file {struct dev_data* private_data; } ;
struct dev_data {scalar_t__ state; int /*<<< orphan*/  lock; scalar_t__ ev_next; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ STATE_DEV_DISABLED ; 
 scalar_t__ STATE_DEV_OPENED ; 
 int /*<<< orphan*/  get_dev (struct dev_data*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dev_open (struct inode *inode, struct file *fd)
{
	struct dev_data		*dev = inode->i_private;
	int			value = -EBUSY;

	spin_lock_irq(&dev->lock);
	if (dev->state == STATE_DEV_DISABLED) {
		dev->ev_next = 0;
		dev->state = STATE_DEV_OPENED;
		fd->private_data = dev;
		get_dev (dev);
		value = 0;
	}
	spin_unlock_irq(&dev->lock);
	return value;
}