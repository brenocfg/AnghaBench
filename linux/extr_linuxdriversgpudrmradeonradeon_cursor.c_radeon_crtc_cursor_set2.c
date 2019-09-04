#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct radeon_device {int dummy; } ;
struct radeon_crtc {scalar_t__ max_cursor_width; scalar_t__ max_cursor_height; scalar_t__ cursor_width; scalar_t__ cursor_height; scalar_t__ cursor_hot_x; scalar_t__ cursor_hot_y; scalar_t__ cursor_x; scalar_t__ cursor_y; struct drm_gem_object* cursor_bo; int /*<<< orphan*/  cursor_addr; int /*<<< orphan*/  crtc_id; } ;
struct radeon_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,scalar_t__) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 scalar_t__ likely (int) ; 
 int radeon_bo_pin_restricted (struct radeon_bo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_cursor_move_locked (struct drm_crtc*,int,int) ; 
 int /*<<< orphan*/  radeon_hide_cursor (struct drm_crtc*) ; 
 int /*<<< orphan*/  radeon_lock_cursor (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  radeon_show_cursor (struct drm_crtc*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

int radeon_crtc_cursor_set2(struct drm_crtc *crtc,
			    struct drm_file *file_priv,
			    uint32_t handle,
			    uint32_t width,
			    uint32_t height,
			    int32_t hot_x,
			    int32_t hot_y)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct radeon_device *rdev = crtc->dev->dev_private;
	struct drm_gem_object *obj;
	struct radeon_bo *robj;
	int ret;

	if (!handle) {
		/* turn off cursor */
		radeon_hide_cursor(crtc);
		obj = NULL;
		goto unpin;
	}

	if ((width > radeon_crtc->max_cursor_width) ||
	    (height > radeon_crtc->max_cursor_height)) {
		DRM_ERROR("bad cursor width or height %d x %d\n", width, height);
		return -EINVAL;
	}

	obj = drm_gem_object_lookup(file_priv, handle);
	if (!obj) {
		DRM_ERROR("Cannot find cursor object %x for crtc %d\n", handle, radeon_crtc->crtc_id);
		return -ENOENT;
	}

	robj = gem_to_radeon_bo(obj);
	ret = radeon_bo_reserve(robj, false);
	if (ret != 0) {
		drm_gem_object_put_unlocked(obj);
		return ret;
	}
	/* Only 27 bit offset for legacy cursor */
	ret = radeon_bo_pin_restricted(robj, RADEON_GEM_DOMAIN_VRAM,
				       ASIC_IS_AVIVO(rdev) ? 0 : 1 << 27,
				       &radeon_crtc->cursor_addr);
	radeon_bo_unreserve(robj);
	if (ret) {
		DRM_ERROR("Failed to pin new cursor BO (%d)\n", ret);
		drm_gem_object_put_unlocked(obj);
		return ret;
	}

	radeon_lock_cursor(crtc, true);

	if (width != radeon_crtc->cursor_width ||
	    height != radeon_crtc->cursor_height ||
	    hot_x != radeon_crtc->cursor_hot_x ||
	    hot_y != radeon_crtc->cursor_hot_y) {
		int x, y;

		x = radeon_crtc->cursor_x + radeon_crtc->cursor_hot_x - hot_x;
		y = radeon_crtc->cursor_y + radeon_crtc->cursor_hot_y - hot_y;

		radeon_crtc->cursor_width = width;
		radeon_crtc->cursor_height = height;
		radeon_crtc->cursor_hot_x = hot_x;
		radeon_crtc->cursor_hot_y = hot_y;

		radeon_cursor_move_locked(crtc, x, y);
	}

	radeon_show_cursor(crtc);

	radeon_lock_cursor(crtc, false);

unpin:
	if (radeon_crtc->cursor_bo) {
		struct radeon_bo *robj = gem_to_radeon_bo(radeon_crtc->cursor_bo);
		ret = radeon_bo_reserve(robj, false);
		if (likely(ret == 0)) {
			radeon_bo_unpin(robj);
			radeon_bo_unreserve(robj);
		}
		drm_gem_object_put_unlocked(radeon_crtc->cursor_bo);
	}

	radeon_crtc->cursor_bo = obj;
	return 0;
}