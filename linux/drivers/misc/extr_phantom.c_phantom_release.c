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
struct phantom_device {int status; int /*<<< orphan*/  open_lock; scalar_t__ opened; } ;
struct inode {int dummy; } ;
struct file {struct phantom_device* private_data; } ;

/* Variables and functions */
 int PHB_NOT_OH ; 
 int PHB_RUNNING ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phantom_status (struct phantom_device*,int) ; 

__attribute__((used)) static int phantom_release(struct inode *inode, struct file *file)
{
	struct phantom_device *dev = file->private_data;

	mutex_lock(&dev->open_lock);

	dev->opened = 0;
	phantom_status(dev, dev->status & ~PHB_RUNNING);
	dev->status &= ~PHB_NOT_OH;

	mutex_unlock(&dev->open_lock);

	return 0;
}