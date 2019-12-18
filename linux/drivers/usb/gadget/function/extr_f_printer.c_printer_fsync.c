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
struct printer_dev {int /*<<< orphan*/  tx_reqs_active; int /*<<< orphan*/  tx_flush_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_reqs; } ;
struct inode {int dummy; } ;
struct file {struct printer_dev* private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
printer_fsync(struct file *fd, loff_t start, loff_t end, int datasync)
{
	struct printer_dev	*dev = fd->private_data;
	struct inode *inode = file_inode(fd);
	unsigned long		flags;
	int			tx_list_empty;

	inode_lock(inode);
	spin_lock_irqsave(&dev->lock, flags);
	tx_list_empty = (likely(list_empty(&dev->tx_reqs)));
	spin_unlock_irqrestore(&dev->lock, flags);

	if (!tx_list_empty) {
		/* Sleep until all data has been sent */
		wait_event_interruptible(dev->tx_flush_wait,
				(likely(list_empty(&dev->tx_reqs_active))));
	}
	inode_unlock(inode);

	return 0;
}