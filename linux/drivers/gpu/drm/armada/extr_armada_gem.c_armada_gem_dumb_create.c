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
typedef  int /*<<< orphan*/  u32 ;
struct drm_mode_create_dumb {size_t pitch; size_t size; size_t height; int /*<<< orphan*/  handle; int /*<<< orphan*/  bpp; int /*<<< orphan*/  width; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct armada_gem_object {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,struct armada_gem_object*,size_t,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct armada_gem_object* armada_gem_alloc_private_object (struct drm_device*,size_t) ; 
 int armada_gem_linear_back (struct drm_device*,struct armada_gem_object*) ; 
 size_t armada_pitch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 

int armada_gem_dumb_create(struct drm_file *file, struct drm_device *dev,
	struct drm_mode_create_dumb *args)
{
	struct armada_gem_object *dobj;
	u32 handle;
	size_t size;
	int ret;

	args->pitch = armada_pitch(args->width, args->bpp);
	args->size = size = args->pitch * args->height;

	dobj = armada_gem_alloc_private_object(dev, size);
	if (dobj == NULL)
		return -ENOMEM;

	ret = armada_gem_linear_back(dev, dobj);
	if (ret)
		goto err;

	ret = drm_gem_handle_create(file, &dobj->obj, &handle);
	if (ret)
		goto err;

	args->handle = handle;

	/* drop reference from allocate - handle holds it now */
	DRM_DEBUG_DRIVER("obj %p size %zu handle %#x\n", dobj, size, handle);
 err:
	drm_gem_object_put_unlocked(&dobj->obj);
	return ret;
}