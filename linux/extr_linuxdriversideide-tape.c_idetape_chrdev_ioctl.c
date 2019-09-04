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
struct file {int dummy; } ;

/* Variables and functions */
 long do_idetape_chrdev_ioctl (struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  ide_tape_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long idetape_chrdev_ioctl(struct file *file,
				unsigned int cmd, unsigned long arg)
{
	long ret;
	mutex_lock(&ide_tape_mutex);
	ret = do_idetape_chrdev_ioctl(file, cmd, arg);
	mutex_unlock(&ide_tape_mutex);
	return ret;
}