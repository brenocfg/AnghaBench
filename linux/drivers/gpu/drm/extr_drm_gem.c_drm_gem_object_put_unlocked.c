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
struct drm_gem_object {int /*<<< orphan*/  refcount; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_1__* driver; } ;
struct TYPE_2__ {scalar_t__ gem_free_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_free ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kref_put_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void
drm_gem_object_put_unlocked(struct drm_gem_object *obj)
{
	struct drm_device *dev;

	if (!obj)
		return;

	dev = obj->dev;

	if (dev->driver->gem_free_object) {
		might_lock(&dev->struct_mutex);
		if (kref_put_mutex(&obj->refcount, drm_gem_object_free,
				&dev->struct_mutex))
			mutex_unlock(&dev->struct_mutex);
	} else {
		kref_put(&obj->refcount, drm_gem_object_free);
	}
}