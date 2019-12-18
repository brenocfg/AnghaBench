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
struct drm_mode_object {scalar_t__ free_cb; int /*<<< orphan*/  refcount; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 

void drm_mode_object_put(struct drm_mode_object *obj)
{
	if (obj->free_cb) {
		DRM_DEBUG("OBJ ID: %d (%d)\n", obj->id, kref_read(&obj->refcount));
		kref_put(&obj->refcount, obj->free_cb);
	}
}