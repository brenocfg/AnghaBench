#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ role; } ;
struct drbd_device {TYPE_3__* resource; int /*<<< orphan*/  open_cnt; TYPE_1__ state; } ;
struct block_device {TYPE_2__* bd_disk; } ;
typedef  int fmode_t ;
struct TYPE_6__ {int /*<<< orphan*/  req_lock; } ;
struct TYPE_5__ {struct drbd_device* private_data; } ;

/* Variables and functions */
 int EMEDIUMTYPE ; 
 int EROFS ; 
 int FMODE_WRITE ; 
 scalar_t__ R_PRIMARY ; 
 int /*<<< orphan*/  drbd_allow_oos ; 
 int /*<<< orphan*/  drbd_main_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int drbd_open(struct block_device *bdev, fmode_t mode)
{
	struct drbd_device *device = bdev->bd_disk->private_data;
	unsigned long flags;
	int rv = 0;

	mutex_lock(&drbd_main_mutex);
	spin_lock_irqsave(&device->resource->req_lock, flags);
	/* to have a stable device->state.role
	 * and no race with updating open_cnt */

	if (device->state.role != R_PRIMARY) {
		if (mode & FMODE_WRITE)
			rv = -EROFS;
		else if (!drbd_allow_oos)
			rv = -EMEDIUMTYPE;
	}

	if (!rv)
		device->open_cnt++;
	spin_unlock_irqrestore(&device->resource->req_lock, flags);
	mutex_unlock(&drbd_main_mutex);

	return rv;
}