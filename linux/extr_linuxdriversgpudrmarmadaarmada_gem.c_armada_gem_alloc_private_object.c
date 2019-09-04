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
struct drm_device {int dummy; } ;
struct armada_gem_object {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,struct armada_gem_object*,size_t) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_gem_private_object_init (struct drm_device*,int /*<<< orphan*/ *,size_t) ; 
 struct armada_gem_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t roundup_gem_size (size_t) ; 

struct armada_gem_object *
armada_gem_alloc_private_object(struct drm_device *dev, size_t size)
{
	struct armada_gem_object *obj;

	size = roundup_gem_size(size);

	obj = kzalloc(sizeof(*obj), GFP_KERNEL);
	if (!obj)
		return NULL;

	drm_gem_private_object_init(dev, &obj->obj, size);

	DRM_DEBUG_DRIVER("alloc private obj %p size %zu\n", obj, size);

	return obj;
}