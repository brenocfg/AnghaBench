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
struct overlay_registers {int dummy; } ;
struct intel_overlay {int color_key; int color_key_enabled; int brightness; int contrast; int saturation; int /*<<< orphan*/  reg_bo; int /*<<< orphan*/  regs; int /*<<< orphan*/  last_flip; struct drm_i915_private* i915; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; struct intel_overlay* overlay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HAS_OVERLAY (struct drm_i915_private*) ; 
 int /*<<< orphan*/  OVERLAY_NEEDS_PHYSICAL (struct drm_i915_private*) ; 
 int get_registers (struct intel_overlay*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (int /*<<< orphan*/ ) ; 
 int i915_gem_object_set_to_gtt_domain (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_request_active (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct intel_overlay*) ; 
 struct intel_overlay* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_polyphase_filter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_reg_attrs (struct intel_overlay*,int /*<<< orphan*/ ) ; 

void intel_setup_overlay(struct drm_i915_private *dev_priv)
{
	struct intel_overlay *overlay;
	int ret;

	if (!HAS_OVERLAY(dev_priv))
		return;

	overlay = kzalloc(sizeof(*overlay), GFP_KERNEL);
	if (!overlay)
		return;

	overlay->i915 = dev_priv;

	overlay->color_key = 0x0101fe;
	overlay->color_key_enabled = true;
	overlay->brightness = -19;
	overlay->contrast = 75;
	overlay->saturation = 146;

	init_request_active(&overlay->last_flip, NULL);

	mutex_lock(&dev_priv->drm.struct_mutex);

	ret = get_registers(overlay, OVERLAY_NEEDS_PHYSICAL(dev_priv));
	if (ret)
		goto out_free;

	ret = i915_gem_object_set_to_gtt_domain(overlay->reg_bo, true);
	if (ret)
		goto out_reg_bo;

	mutex_unlock(&dev_priv->drm.struct_mutex);

	memset_io(overlay->regs, 0, sizeof(struct overlay_registers));
	update_polyphase_filter(overlay->regs);
	update_reg_attrs(overlay, overlay->regs);

	dev_priv->overlay = overlay;
	DRM_INFO("Initialized overlay support.\n");
	return;

out_reg_bo:
	i915_gem_object_put(overlay->reg_bo);
out_free:
	mutex_unlock(&dev_priv->drm.struct_mutex);
	kfree(overlay);
}