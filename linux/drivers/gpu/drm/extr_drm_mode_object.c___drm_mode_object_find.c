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
typedef  scalar_t__ uint32_t ;
struct drm_mode_object {scalar_t__ type; scalar_t__ id; int /*<<< orphan*/  refcount; scalar_t__ free_cb; } ;
struct drm_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  idr_mutex; int /*<<< orphan*/  object_idr; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_OBJECT_ANY ; 
 int /*<<< orphan*/  _drm_lease_held (struct drm_file*,scalar_t__) ; 
 scalar_t__ drm_mode_object_lease_required (scalar_t__) ; 
 struct drm_mode_object* idr_find (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct drm_mode_object *__drm_mode_object_find(struct drm_device *dev,
					       struct drm_file *file_priv,
					       uint32_t id, uint32_t type)
{
	struct drm_mode_object *obj = NULL;

	mutex_lock(&dev->mode_config.idr_mutex);
	obj = idr_find(&dev->mode_config.object_idr, id);
	if (obj && type != DRM_MODE_OBJECT_ANY && obj->type != type)
		obj = NULL;
	if (obj && obj->id != id)
		obj = NULL;

	if (obj && drm_mode_object_lease_required(obj->type) &&
	    !_drm_lease_held(file_priv, obj->id))
		obj = NULL;

	if (obj && obj->free_cb) {
		if (!kref_get_unless_zero(&obj->refcount))
			obj = NULL;
	}
	mutex_unlock(&dev->mode_config.idr_mutex);

	return obj;
}