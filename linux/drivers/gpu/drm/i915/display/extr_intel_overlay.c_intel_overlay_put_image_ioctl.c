#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_overlay {int pfit_active; int pfit_vscale_ratio; struct intel_crtc* crtc; } ;
struct intel_crtc {TYPE_2__* config; struct intel_overlay* overlay; } ;
struct drm_intel_overlay_put_image {int flags; int dst_y; int dst_height; scalar_t__ src_scan_height; scalar_t__ src_height; scalar_t__ src_scan_width; scalar_t__ src_width; int /*<<< orphan*/  bo_handle; int /*<<< orphan*/  crtc_id; } ;
struct drm_i915_private {struct intel_overlay* overlay; } ;
struct drm_i915_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_3__ {int control; } ;
struct TYPE_4__ {int pipe_src_w; TYPE_1__ gmch_pfit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int I915_OVERLAY_ENABLE ; 
 int PFIT_ENABLE ; 
 int check_overlay_dst (struct intel_overlay*,struct drm_intel_overlay_put_image*) ; 
 int check_overlay_possible_on_crtc (struct intel_overlay*,struct intel_crtc*) ; 
 int check_overlay_scaling (struct drm_intel_overlay_put_image*) ; 
 int check_overlay_src (struct drm_i915_private*,struct drm_intel_overlay_put_image*,struct drm_i915_gem_object*) ; 
 struct drm_crtc* drm_crtc_find (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 scalar_t__ i915_gem_object_is_tiled (struct drm_i915_gem_object*) ; 
 struct drm_i915_gem_object* i915_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int intel_overlay_do_put_image (struct intel_overlay*,struct drm_i915_gem_object*,struct drm_intel_overlay_put_image*) ; 
 int intel_overlay_recover_from_interrupt (struct intel_overlay*) ; 
 int intel_overlay_switch_off (struct intel_overlay*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  update_pfit_vscale_ratio (struct intel_overlay*) ; 

int intel_overlay_put_image_ioctl(struct drm_device *dev, void *data,
				  struct drm_file *file_priv)
{
	struct drm_intel_overlay_put_image *params = data;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_overlay *overlay;
	struct drm_crtc *drmmode_crtc;
	struct intel_crtc *crtc;
	struct drm_i915_gem_object *new_bo;
	int ret;

	overlay = dev_priv->overlay;
	if (!overlay) {
		DRM_DEBUG("userspace bug: no overlay\n");
		return -ENODEV;
	}

	if (!(params->flags & I915_OVERLAY_ENABLE)) {
		drm_modeset_lock_all(dev);
		mutex_lock(&dev->struct_mutex);

		ret = intel_overlay_switch_off(overlay);

		mutex_unlock(&dev->struct_mutex);
		drm_modeset_unlock_all(dev);

		return ret;
	}

	drmmode_crtc = drm_crtc_find(dev, file_priv, params->crtc_id);
	if (!drmmode_crtc)
		return -ENOENT;
	crtc = to_intel_crtc(drmmode_crtc);

	new_bo = i915_gem_object_lookup(file_priv, params->bo_handle);
	if (!new_bo)
		return -ENOENT;

	drm_modeset_lock_all(dev);
	mutex_lock(&dev->struct_mutex);

	if (i915_gem_object_is_tiled(new_bo)) {
		DRM_DEBUG_KMS("buffer used for overlay image can not be tiled\n");
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = intel_overlay_recover_from_interrupt(overlay);
	if (ret != 0)
		goto out_unlock;

	if (overlay->crtc != crtc) {
		ret = intel_overlay_switch_off(overlay);
		if (ret != 0)
			goto out_unlock;

		ret = check_overlay_possible_on_crtc(overlay, crtc);
		if (ret != 0)
			goto out_unlock;

		overlay->crtc = crtc;
		crtc->overlay = overlay;

		/* line too wide, i.e. one-line-mode */
		if (crtc->config->pipe_src_w > 1024 &&
		    crtc->config->gmch_pfit.control & PFIT_ENABLE) {
			overlay->pfit_active = true;
			update_pfit_vscale_ratio(overlay);
		} else
			overlay->pfit_active = false;
	}

	ret = check_overlay_dst(overlay, params);
	if (ret != 0)
		goto out_unlock;

	if (overlay->pfit_active) {
		params->dst_y = (((u32)params->dst_y << 12) /
				 overlay->pfit_vscale_ratio);
		/* shifting right rounds downwards, so add 1 */
		params->dst_height = (((u32)params->dst_height << 12) /
				 overlay->pfit_vscale_ratio) + 1;
	}

	if (params->src_scan_height > params->src_height ||
	    params->src_scan_width > params->src_width) {
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = check_overlay_src(dev_priv, params, new_bo);
	if (ret != 0)
		goto out_unlock;

	/* Check scaling after src size to prevent a divide-by-zero. */
	ret = check_overlay_scaling(params);
	if (ret != 0)
		goto out_unlock;

	ret = intel_overlay_do_put_image(overlay, new_bo, params);
	if (ret != 0)
		goto out_unlock;

	mutex_unlock(&dev->struct_mutex);
	drm_modeset_unlock_all(dev);
	i915_gem_object_put(new_bo);

	return 0;

out_unlock:
	mutex_unlock(&dev->struct_mutex);
	drm_modeset_unlock_all(dev);
	i915_gem_object_put(new_bo);

	return ret;
}