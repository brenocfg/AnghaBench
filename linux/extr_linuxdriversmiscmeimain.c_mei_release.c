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
struct mei_device {int /*<<< orphan*/  device_lock; } ;
struct mei_cl {struct mei_device* dev; } ;
struct inode {int dummy; } ;
struct file {struct mei_cl* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int /*<<< orphan*/  kfree (struct mei_cl*) ; 
 int mei_cl_disconnect (struct mei_cl*) ; 
 int /*<<< orphan*/  mei_cl_flush_queues (struct mei_cl*,struct file*) ; 
 int /*<<< orphan*/  mei_cl_unlink (struct mei_cl*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mei_release(struct inode *inode, struct file *file)
{
	struct mei_cl *cl = file->private_data;
	struct mei_device *dev;
	int rets;

	if (WARN_ON(!cl || !cl->dev))
		return -ENODEV;

	dev = cl->dev;

	mutex_lock(&dev->device_lock);

	rets = mei_cl_disconnect(cl);

	mei_cl_flush_queues(cl, file);
	cl_dbg(dev, cl, "removing\n");

	mei_cl_unlink(cl);

	file->private_data = NULL;

	kfree(cl);

	mutex_unlock(&dev->device_lock);
	return rets;
}