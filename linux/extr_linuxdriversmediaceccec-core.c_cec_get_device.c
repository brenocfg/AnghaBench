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
struct cec_devnode {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cec_get_device(struct cec_devnode *devnode)
{
	/*
	 * Check if the cec device is available. This needs to be done with
	 * the devnode->lock held to prevent an open/unregister race:
	 * without the lock, the device could be unregistered and freed between
	 * the devnode->registered check and get_device() calls, leading to
	 * a crash.
	 */
	mutex_lock(&devnode->lock);
	/*
	 * return ENXIO if the cec device has been removed
	 * already or if it is not registered anymore.
	 */
	if (!devnode->registered) {
		mutex_unlock(&devnode->lock);
		return -ENXIO;
	}
	/* and increase the device refcount */
	get_device(&devnode->dev);
	mutex_unlock(&devnode->lock);
	return 0;
}