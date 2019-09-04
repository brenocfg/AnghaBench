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
struct file {void* private_data; } ;
struct TYPE_3__ {int minor; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  aoechr_mutex ; 
 TYPE_1__* chardevs ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aoechr_open(struct inode *inode, struct file *filp)
{
	int n, i;

	mutex_lock(&aoechr_mutex);
	n = iminor(inode);
	filp->private_data = (void *) (unsigned long) n;

	for (i = 0; i < ARRAY_SIZE(chardevs); ++i)
		if (chardevs[i].minor == n) {
			mutex_unlock(&aoechr_mutex);
			return 0;
		}
	mutex_unlock(&aoechr_mutex);
	return -EINVAL;
}