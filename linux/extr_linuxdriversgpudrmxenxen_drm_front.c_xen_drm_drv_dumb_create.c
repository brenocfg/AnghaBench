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
struct xen_drm_front_drm_info {int /*<<< orphan*/  front_info; } ;
struct drm_mode_create_dumb {int pitch; int width; int bpp; int size; int height; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct xen_drm_front_drm_info* dev_private; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ IS_ERR_OR_NULL (struct drm_gem_object*) ; 
 int PTR_ERR (struct drm_gem_object*) ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int xen_drm_front_dbuf_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_drm_front_dbuf_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_drm_front_dbuf_to_cookie (struct drm_gem_object*) ; 
 struct drm_gem_object* xen_drm_front_gem_create (struct drm_device*,int) ; 
 int /*<<< orphan*/  xen_drm_front_gem_get_pages (struct drm_gem_object*) ; 

__attribute__((used)) static int xen_drm_drv_dumb_create(struct drm_file *filp,
				   struct drm_device *dev,
				   struct drm_mode_create_dumb *args)
{
	struct xen_drm_front_drm_info *drm_info = dev->dev_private;
	struct drm_gem_object *obj;
	int ret;

	/*
	 * Dumb creation is a two stage process: first we create a fully
	 * constructed GEM object which is communicated to the backend, and
	 * only after that we can create GEM's handle. This is done so,
	 * because of the possible races: once you create a handle it becomes
	 * immediately visible to user-space, so the latter can try accessing
	 * object without pages etc.
	 * For details also see drm_gem_handle_create
	 */
	args->pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	args->size = args->pitch * args->height;

	obj = xen_drm_front_gem_create(dev, args->size);
	if (IS_ERR_OR_NULL(obj)) {
		ret = PTR_ERR(obj);
		goto fail;
	}

	ret = xen_drm_front_dbuf_create(drm_info->front_info,
					xen_drm_front_dbuf_to_cookie(obj),
					args->width, args->height, args->bpp,
					args->size,
					xen_drm_front_gem_get_pages(obj));
	if (ret)
		goto fail_backend;

	/* This is the tail of GEM object creation */
	ret = drm_gem_handle_create(filp, obj, &args->handle);
	if (ret)
		goto fail_handle;

	/* Drop reference from allocate - handle holds it now */
	drm_gem_object_put_unlocked(obj);
	return 0;

fail_handle:
	xen_drm_front_dbuf_destroy(drm_info->front_info,
				   xen_drm_front_dbuf_to_cookie(obj));
fail_backend:
	/* drop reference from allocate */
	drm_gem_object_put_unlocked(obj);
fail:
	DRM_ERROR("Failed to create dumb buffer: %d\n", ret);
	return ret;
}