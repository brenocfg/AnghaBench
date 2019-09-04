#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct loop_device {int /*<<< orphan*/  lo_refcnt; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct loop_device* private_data; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_ctl_mutex ; 
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lo_open(struct block_device *bdev, fmode_t mode)
{
	struct loop_device *lo;
	int err;

	err = mutex_lock_killable(&loop_ctl_mutex);
	if (err)
		return err;
	lo = bdev->bd_disk->private_data;
	if (!lo) {
		err = -ENXIO;
		goto out;
	}

	atomic_inc(&lo->lo_refcnt);
out:
	mutex_unlock(&loop_ctl_mutex);
	return err;
}