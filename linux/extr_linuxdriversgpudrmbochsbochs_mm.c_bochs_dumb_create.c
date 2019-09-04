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
struct drm_mode_create_dumb {int pitch; int width; int bpp; int size; int height; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int bochs_gem_create (struct drm_device*,int,int,struct drm_gem_object**) ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 

int bochs_dumb_create(struct drm_file *file, struct drm_device *dev,
		      struct drm_mode_create_dumb *args)
{
	struct drm_gem_object *gobj;
	u32 handle;
	int ret;

	args->pitch = args->width * ((args->bpp + 7) / 8);
	args->size = args->pitch * args->height;

	ret = bochs_gem_create(dev, args->size, false,
			       &gobj);
	if (ret)
		return ret;

	ret = drm_gem_handle_create(file, gobj, &handle);
	drm_gem_object_unreference_unlocked(gobj);
	if (ret)
		return ret;

	args->handle = handle;
	return 0;
}