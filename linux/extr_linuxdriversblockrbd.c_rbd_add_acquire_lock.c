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
struct TYPE_2__ {int features; } ;
struct rbd_device {int /*<<< orphan*/  lock_rwsem; TYPE_1__ header; } ;

/* Variables and functions */
 int EINVAL ; 
 int EROFS ; 
 int RBD_FEATURE_EXCLUSIVE_LOCK ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int rbd_wait_state_locked (struct rbd_device*,int) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rbd_add_acquire_lock(struct rbd_device *rbd_dev)
{
	int ret;

	if (!(rbd_dev->header.features & RBD_FEATURE_EXCLUSIVE_LOCK)) {
		rbd_warn(rbd_dev, "exclusive-lock feature is not enabled");
		return -EINVAL;
	}

	/* FIXME: "rbd map --exclusive" should be in interruptible */
	down_read(&rbd_dev->lock_rwsem);
	ret = rbd_wait_state_locked(rbd_dev, true);
	up_read(&rbd_dev->lock_rwsem);
	if (ret) {
		rbd_warn(rbd_dev, "failed to acquire exclusive lock");
		return -EROFS;
	}

	return 0;
}