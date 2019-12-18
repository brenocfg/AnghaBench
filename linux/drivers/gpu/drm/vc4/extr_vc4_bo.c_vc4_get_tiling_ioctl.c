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
struct vc4_bo {scalar_t__ t_format; } ;
struct drm_vc4_get_tiling {scalar_t__ flags; scalar_t__ modifier; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED ; 
 scalar_t__ DRM_FORMAT_MOD_NONE ; 
 int EINVAL ; 
 int ENOENT ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 

int vc4_get_tiling_ioctl(struct drm_device *dev, void *data,
			 struct drm_file *file_priv)
{
	struct drm_vc4_get_tiling *args = data;
	struct drm_gem_object *gem_obj;
	struct vc4_bo *bo;

	if (args->flags != 0 || args->modifier != 0)
		return -EINVAL;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	if (!gem_obj) {
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		return -ENOENT;
	}
	bo = to_vc4_bo(gem_obj);

	if (bo->t_format)
		args->modifier = DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED;
	else
		args->modifier = DRM_FORMAT_MOD_NONE;

	drm_gem_object_put_unlocked(gem_obj);

	return 0;
}