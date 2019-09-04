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
typedef  int u64 ;
struct drm_mode_create_dumb {int width; int height; int pitch; int /*<<< orphan*/  size; int /*<<< orphan*/  handle; int /*<<< orphan*/  bpp; } ;
struct drm_gem_object {int /*<<< orphan*/  size; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_gem_object*) ; 
 int PTR_ERR (struct drm_gem_object*) ; 
 struct drm_gem_object* vkms_gem_create (struct drm_device*,struct drm_file*,int /*<<< orphan*/ *,int) ; 

int vkms_dumb_create(struct drm_file *file, struct drm_device *dev,
		     struct drm_mode_create_dumb *args)
{
	struct drm_gem_object *gem_obj;
	u64 pitch, size;

	if (!args || !dev || !file)
		return -EINVAL;

	pitch = args->width * DIV_ROUND_UP(args->bpp, 8);
	size = pitch * args->height;

	if (!size)
		return -EINVAL;

	gem_obj = vkms_gem_create(dev, file, &args->handle, size);
	if (IS_ERR(gem_obj))
		return PTR_ERR(gem_obj);

	args->size = gem_obj->size;
	args->pitch = pitch;

	DRM_DEBUG_DRIVER("Created object of size %lld\n", size);

	return 0;
}