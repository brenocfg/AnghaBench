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
struct intel_overlay {int brightness; int contrast; int saturation; int color_key_enabled; scalar_t__ active; int /*<<< orphan*/  regs; int /*<<< orphan*/  color_key; } ;
struct drm_intel_overlay_attrs {int flags; int brightness; int contrast; int saturation; void* gamma5; void* gamma4; void* gamma3; void* gamma2; void* gamma1; void* gamma0; int /*<<< orphan*/  color_key; } ;
struct drm_i915_private {struct intel_overlay* overlay; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int I915_OVERLAY_DISABLE_DEST_COLORKEY ; 
 int I915_OVERLAY_UPDATE_ATTRS ; 
 int I915_OVERLAY_UPDATE_GAMMA ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  OGAMC0 ; 
 int /*<<< orphan*/  OGAMC1 ; 
 int /*<<< orphan*/  OGAMC2 ; 
 int /*<<< orphan*/  OGAMC3 ; 
 int /*<<< orphan*/  OGAMC4 ; 
 int /*<<< orphan*/  OGAMC5 ; 
 int check_gamma (struct drm_intel_overlay_attrs*) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int /*<<< orphan*/  update_reg_attrs (struct intel_overlay*,int /*<<< orphan*/ ) ; 

int intel_overlay_attrs_ioctl(struct drm_device *dev, void *data,
			      struct drm_file *file_priv)
{
	struct drm_intel_overlay_attrs *attrs = data;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_overlay *overlay;
	int ret;

	overlay = dev_priv->overlay;
	if (!overlay) {
		DRM_DEBUG("userspace bug: no overlay\n");
		return -ENODEV;
	}

	drm_modeset_lock_all(dev);
	mutex_lock(&dev->struct_mutex);

	ret = -EINVAL;
	if (!(attrs->flags & I915_OVERLAY_UPDATE_ATTRS)) {
		attrs->color_key  = overlay->color_key;
		attrs->brightness = overlay->brightness;
		attrs->contrast   = overlay->contrast;
		attrs->saturation = overlay->saturation;

		if (!IS_GEN(dev_priv, 2)) {
			attrs->gamma0 = I915_READ(OGAMC0);
			attrs->gamma1 = I915_READ(OGAMC1);
			attrs->gamma2 = I915_READ(OGAMC2);
			attrs->gamma3 = I915_READ(OGAMC3);
			attrs->gamma4 = I915_READ(OGAMC4);
			attrs->gamma5 = I915_READ(OGAMC5);
		}
	} else {
		if (attrs->brightness < -128 || attrs->brightness > 127)
			goto out_unlock;
		if (attrs->contrast > 255)
			goto out_unlock;
		if (attrs->saturation > 1023)
			goto out_unlock;

		overlay->color_key  = attrs->color_key;
		overlay->brightness = attrs->brightness;
		overlay->contrast   = attrs->contrast;
		overlay->saturation = attrs->saturation;

		update_reg_attrs(overlay, overlay->regs);

		if (attrs->flags & I915_OVERLAY_UPDATE_GAMMA) {
			if (IS_GEN(dev_priv, 2))
				goto out_unlock;

			if (overlay->active) {
				ret = -EBUSY;
				goto out_unlock;
			}

			ret = check_gamma(attrs);
			if (ret)
				goto out_unlock;

			I915_WRITE(OGAMC0, attrs->gamma0);
			I915_WRITE(OGAMC1, attrs->gamma1);
			I915_WRITE(OGAMC2, attrs->gamma2);
			I915_WRITE(OGAMC3, attrs->gamma3);
			I915_WRITE(OGAMC4, attrs->gamma4);
			I915_WRITE(OGAMC5, attrs->gamma5);
		}
	}
	overlay->color_key_enabled = (attrs->flags & I915_OVERLAY_DISABLE_DEST_COLORKEY) == 0;

	ret = 0;
out_unlock:
	mutex_unlock(&dev->struct_mutex);
	drm_modeset_unlock_all(dev);

	return ret;
}