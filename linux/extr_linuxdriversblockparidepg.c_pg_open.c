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
struct pg {int /*<<< orphan*/  name; int /*<<< orphan*/  access; int /*<<< orphan*/ * bufptr; scalar_t__ busy; int /*<<< orphan*/  present; } ;
struct inode {int dummy; } ;
struct file {struct pg* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PG_MAX_DATA ; 
 int PG_UNITS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pg* devices ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_identify (struct pg*,int) ; 
 int /*<<< orphan*/  pg_mutex ; 
 int /*<<< orphan*/  pg_reset (struct pg*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int verbose ; 

__attribute__((used)) static int pg_open(struct inode *inode, struct file *file)
{
	int unit = iminor(inode) & 0x7f;
	struct pg *dev = &devices[unit];
	int ret = 0;

	mutex_lock(&pg_mutex);
	if ((unit >= PG_UNITS) || (!dev->present)) {
		ret = -ENODEV;
		goto out;
	}

	if (test_and_set_bit(0, &dev->access)) {
		ret = -EBUSY;
		goto out;
	}

	if (dev->busy) {
		pg_reset(dev);
		dev->busy = 0;
	}

	pg_identify(dev, (verbose > 1));

	dev->bufptr = kmalloc(PG_MAX_DATA, GFP_KERNEL);
	if (dev->bufptr == NULL) {
		clear_bit(0, &dev->access);
		printk("%s: buffer allocation failed\n", dev->name);
		ret = -ENOMEM;
		goto out;
	}

	file->private_data = dev;

out:
	mutex_unlock(&pg_mutex);
	return ret;
}