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
 long __mptctl_ioctl (struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  mpctl_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
mptctl_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;
	mutex_lock(&mpctl_mutex);
	ret = __mptctl_ioctl(file, cmd, arg);
	mutex_unlock(&mpctl_mutex);
	return ret;
}