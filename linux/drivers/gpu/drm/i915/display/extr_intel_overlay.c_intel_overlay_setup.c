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
struct intel_overlay {int color_key; int color_key_enabled; int brightness; int contrast; int saturation; int /*<<< orphan*/  regs; int /*<<< orphan*/  last_flip; int /*<<< orphan*/  context; struct drm_i915_private* i915; } ;
struct drm_i915_private {struct intel_overlay* overlay; TYPE_1__** engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  kernel_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HAS_ENGINE (struct drm_i915_private*,size_t) ; 
 int /*<<< orphan*/  HAS_OVERLAY (struct drm_i915_private*) ; 
 int /*<<< orphan*/  OVERLAY_NEEDS_PHYSICAL (struct drm_i915_private*) ; 
 size_t RCS0 ; 
 int get_registers (struct intel_overlay*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_active_init (struct drm_i915_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_overlay_last_flip_retire ; 
 int /*<<< orphan*/  kfree (struct intel_overlay*) ; 
 struct intel_overlay* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_polyphase_filter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_reg_attrs (struct intel_overlay*,int /*<<< orphan*/ ) ; 

void intel_overlay_setup(struct drm_i915_private *dev_priv)
{
	struct intel_overlay *overlay;
	int ret;

	if (!HAS_OVERLAY(dev_priv))
		return;

	if (!HAS_ENGINE(dev_priv, RCS0))
		return;

	overlay = kzalloc(sizeof(*overlay), GFP_KERNEL);
	if (!overlay)
		return;

	overlay->i915 = dev_priv;
	overlay->context = dev_priv->engine[RCS0]->kernel_context;
	GEM_BUG_ON(!overlay->context);

	overlay->color_key = 0x0101fe;
	overlay->color_key_enabled = true;
	overlay->brightness = -19;
	overlay->contrast = 75;
	overlay->saturation = 146;

	i915_active_init(dev_priv,
			 &overlay->last_flip,
			 NULL, intel_overlay_last_flip_retire);

	ret = get_registers(overlay, OVERLAY_NEEDS_PHYSICAL(dev_priv));
	if (ret)
		goto out_free;

	memset_io(overlay->regs, 0, sizeof(struct overlay_registers));
	update_polyphase_filter(overlay->regs);
	update_reg_attrs(overlay, overlay->regs);

	dev_priv->overlay = overlay;
	DRM_INFO("Initialized overlay support.\n");
	return;

out_free:
	kfree(overlay);
}