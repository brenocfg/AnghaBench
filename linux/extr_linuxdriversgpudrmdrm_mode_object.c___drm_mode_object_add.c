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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_mode_object {int id; void (* free_cb ) (struct kref*) ;int /*<<< orphan*/  refcount; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  idr_mutex; int /*<<< orphan*/  crtc_idr; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_alloc (int /*<<< orphan*/ *,struct drm_mode_object*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int __drm_mode_object_add(struct drm_device *dev, struct drm_mode_object *obj,
			  uint32_t obj_type, bool register_obj,
			  void (*obj_free_cb)(struct kref *kref))
{
	int ret;

	mutex_lock(&dev->mode_config.idr_mutex);
	ret = idr_alloc(&dev->mode_config.crtc_idr, register_obj ? obj : NULL, 1, 0, GFP_KERNEL);
	if (ret >= 0) {
		/*
		 * Set up the object linking under the protection of the idr
		 * lock so that other users can't see inconsistent state.
		 */
		obj->id = ret;
		obj->type = obj_type;
		if (obj_free_cb) {
			obj->free_cb = obj_free_cb;
			kref_init(&obj->refcount);
		}
	}
	mutex_unlock(&dev->mode_config.idr_mutex);

	return ret < 0 ? ret : 0;
}