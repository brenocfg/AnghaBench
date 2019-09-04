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
struct drm_gem_object {int dummy; } ;
struct drm_vgem_gem_object {struct drm_gem_object base; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct drm_gem_object* ERR_CAST (struct drm_vgem_gem_object*) ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_vgem_gem_object*) ; 
 struct drm_vgem_gem_object* __vgem_gem_create (struct drm_device*,unsigned long) ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,unsigned int*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 

__attribute__((used)) static struct drm_gem_object *vgem_gem_create(struct drm_device *dev,
					      struct drm_file *file,
					      unsigned int *handle,
					      unsigned long size)
{
	struct drm_vgem_gem_object *obj;
	int ret;

	obj = __vgem_gem_create(dev, size);
	if (IS_ERR(obj))
		return ERR_CAST(obj);

	ret = drm_gem_handle_create(file, &obj->base, handle);
	drm_gem_object_put_unlocked(&obj->base);
	if (ret)
		return ERR_PTR(ret);

	return &obj->base;
}