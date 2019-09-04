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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_mode_object {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_OBJECT_FB ; 
 struct drm_mode_object* __drm_mode_object_find (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_framebuffer* obj_to_fb (struct drm_mode_object*) ; 

struct drm_framebuffer *drm_framebuffer_lookup(struct drm_device *dev,
					       struct drm_file *file_priv,
					       uint32_t id)
{
	struct drm_mode_object *obj;
	struct drm_framebuffer *fb = NULL;

	obj = __drm_mode_object_find(dev, file_priv, id, DRM_MODE_OBJECT_FB);
	if (obj)
		fb = obj_to_fb(obj);
	return fb;
}