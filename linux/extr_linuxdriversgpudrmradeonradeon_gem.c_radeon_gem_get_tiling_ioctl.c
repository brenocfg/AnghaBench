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
struct radeon_bo {int dummy; } ;
struct drm_radeon_gem_get_tiling {int /*<<< orphan*/  pitch; int /*<<< orphan*/  tiling_flags; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int ENOENT ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  radeon_bo_get_tiling_flags (struct radeon_bo*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 scalar_t__ unlikely (int) ; 

int radeon_gem_get_tiling_ioctl(struct drm_device *dev, void *data,
				struct drm_file *filp)
{
	struct drm_radeon_gem_get_tiling *args = data;
	struct drm_gem_object *gobj;
	struct radeon_bo *rbo;
	int r = 0;

	DRM_DEBUG("\n");
	gobj = drm_gem_object_lookup(filp, args->handle);
	if (gobj == NULL)
		return -ENOENT;
	rbo = gem_to_radeon_bo(gobj);
	r = radeon_bo_reserve(rbo, false);
	if (unlikely(r != 0))
		goto out;
	radeon_bo_get_tiling_flags(rbo, &args->tiling_flags, &args->pitch);
	radeon_bo_unreserve(rbo);
out:
	drm_gem_object_put_unlocked(gobj);
	return r;
}