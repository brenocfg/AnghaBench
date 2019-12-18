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
typedef  union omap_gem_size {int dummy; } omap_gem_size ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  omap_gem_free_object (struct drm_gem_object*) ; 
 struct drm_gem_object* omap_gem_new (struct drm_device*,union omap_gem_size,int /*<<< orphan*/ ) ; 

int omap_gem_new_handle(struct drm_device *dev, struct drm_file *file,
		union omap_gem_size gsize, u32 flags, u32 *handle)
{
	struct drm_gem_object *obj;
	int ret;

	obj = omap_gem_new(dev, gsize, flags);
	if (!obj)
		return -ENOMEM;

	ret = drm_gem_handle_create(file, obj, handle);
	if (ret) {
		omap_gem_free_object(obj);
		return ret;
	}

	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put_unlocked(obj);

	return 0;
}