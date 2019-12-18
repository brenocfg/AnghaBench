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
struct drm_device {int unplugged; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_unplug_srcu ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

void drm_dev_unplug(struct drm_device *dev)
{
	/*
	 * After synchronizing any critical read section is guaranteed to see
	 * the new value of ->unplugged, and any critical section which might
	 * still have seen the old value of ->unplugged is guaranteed to have
	 * finished.
	 */
	dev->unplugged = true;
	synchronize_srcu(&drm_unplug_srcu);

	drm_dev_unregister(dev);
}