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
struct drm_device {scalar_t__ unplugged; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_unplug_srcu ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

bool drm_dev_enter(struct drm_device *dev, int *idx)
{
	*idx = srcu_read_lock(&drm_unplug_srcu);

	if (dev->unplugged) {
		srcu_read_unlock(&drm_unplug_srcu, *idx);
		return false;
	}

	return true;
}