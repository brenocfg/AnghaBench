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
typedef  scalar_t__ uint32_t ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct amdgpu_crtc {scalar_t__ max_cursor_width; scalar_t__ max_cursor_height; scalar_t__ cursor_width; scalar_t__ cursor_height; scalar_t__ cursor_hot_x; scalar_t__ cursor_hot_y; scalar_t__ cursor_x; scalar_t__ cursor_y; struct drm_gem_object* cursor_bo; int /*<<< orphan*/  cursor_addr; int /*<<< orphan*/  crtc_id; } ;
struct amdgpu_bo {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int amdgpu_bo_pin (struct amdgpu_bo*,int /*<<< orphan*/ ) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  dce_v11_0_cursor_move_locked (struct drm_crtc*,int,int) ; 
 int /*<<< orphan*/  dce_v11_0_hide_cursor (struct drm_crtc*) ; 
 int /*<<< orphan*/  dce_v11_0_lock_cursor (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  dce_v11_0_show_cursor (struct drm_crtc*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,scalar_t__) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 scalar_t__ likely (int) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int dce_v11_0_crtc_cursor_set2(struct drm_crtc *crtc,
				      struct drm_file *file_priv,
				      uint32_t handle,
				      uint32_t width,
				      uint32_t height,
				      int32_t hot_x,
				      int32_t hot_y)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct drm_gem_object *obj;
	struct amdgpu_bo *aobj;
	int ret;

	if (!handle) {
		/* turn off cursor */
		dce_v11_0_hide_cursor(crtc);
		obj = NULL;
		goto unpin;
	}

	if ((width > amdgpu_crtc->max_cursor_width) ||
	    (height > amdgpu_crtc->max_cursor_height)) {
		DRM_ERROR("bad cursor width or height %d x %d\n", width, height);
		return -EINVAL;
	}

	obj = drm_gem_object_lookup(file_priv, handle);
	if (!obj) {
		DRM_ERROR("Cannot find cursor object %x for crtc %d\n", handle, amdgpu_crtc->crtc_id);
		return -ENOENT;
	}

	aobj = gem_to_amdgpu_bo(obj);
	ret = amdgpu_bo_reserve(aobj, false);
	if (ret != 0) {
		drm_gem_object_put_unlocked(obj);
		return ret;
	}

	ret = amdgpu_bo_pin(aobj, AMDGPU_GEM_DOMAIN_VRAM);
	amdgpu_bo_unreserve(aobj);
	if (ret) {
		DRM_ERROR("Failed to pin new cursor BO (%d)\n", ret);
		drm_gem_object_put_unlocked(obj);
		return ret;
	}
	amdgpu_crtc->cursor_addr = amdgpu_bo_gpu_offset(aobj);

	dce_v11_0_lock_cursor(crtc, true);

	if (width != amdgpu_crtc->cursor_width ||
	    height != amdgpu_crtc->cursor_height ||
	    hot_x != amdgpu_crtc->cursor_hot_x ||
	    hot_y != amdgpu_crtc->cursor_hot_y) {
		int x, y;

		x = amdgpu_crtc->cursor_x + amdgpu_crtc->cursor_hot_x - hot_x;
		y = amdgpu_crtc->cursor_y + amdgpu_crtc->cursor_hot_y - hot_y;

		dce_v11_0_cursor_move_locked(crtc, x, y);

		amdgpu_crtc->cursor_width = width;
		amdgpu_crtc->cursor_height = height;
		amdgpu_crtc->cursor_hot_x = hot_x;
		amdgpu_crtc->cursor_hot_y = hot_y;
	}

	dce_v11_0_show_cursor(crtc);
	dce_v11_0_lock_cursor(crtc, false);

unpin:
	if (amdgpu_crtc->cursor_bo) {
		struct amdgpu_bo *aobj = gem_to_amdgpu_bo(amdgpu_crtc->cursor_bo);
		ret = amdgpu_bo_reserve(aobj, true);
		if (likely(ret == 0)) {
			amdgpu_bo_unpin(aobj);
			amdgpu_bo_unreserve(aobj);
		}
		drm_gem_object_put_unlocked(amdgpu_crtc->cursor_bo);
	}

	amdgpu_crtc->cursor_bo = obj;
	return 0;
}