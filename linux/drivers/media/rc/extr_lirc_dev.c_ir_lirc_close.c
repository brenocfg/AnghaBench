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
struct rc_dev {scalar_t__ driver_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  lirc_fh_lock; } ;
struct lirc_fh {int /*<<< orphan*/  scancodes; int /*<<< orphan*/  rawir; int /*<<< orphan*/  list; struct rc_dev* rc; } ;
struct inode {int dummy; } ;
struct file {struct lirc_fh* private_data; } ;

/* Variables and functions */
 scalar_t__ RC_DRIVER_IR_RAW ; 
 scalar_t__ RC_DRIVER_IR_RAW_TX ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lirc_fh*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_close (struct rc_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ir_lirc_close(struct inode *inode, struct file *file)
{
	struct lirc_fh *fh = file->private_data;
	struct rc_dev *dev = fh->rc;
	unsigned long flags;

	spin_lock_irqsave(&dev->lirc_fh_lock, flags);
	list_del(&fh->list);
	spin_unlock_irqrestore(&dev->lirc_fh_lock, flags);

	if (dev->driver_type == RC_DRIVER_IR_RAW)
		kfifo_free(&fh->rawir);
	if (dev->driver_type != RC_DRIVER_IR_RAW_TX)
		kfifo_free(&fh->scancodes);
	kfree(fh);

	rc_close(dev);
	put_device(&dev->dev);

	return 0;
}