#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* state; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_3__ base; } ;
struct intel_sdvo_connector {TYPE_2__ base; } ;
struct intel_sdvo {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  picture_aspect_ratio; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_PICTURE_ASPECT_NONE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_MOBILE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_attach_aspect_ratio_property (TYPE_3__*) ; 
 int /*<<< orphan*/  intel_attach_broadcast_rgb_property (TYPE_3__*) ; 
 int /*<<< orphan*/  intel_attach_force_audio_property (TYPE_3__*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_sdvo_add_hdmi_properties(struct intel_sdvo *intel_sdvo,
			       struct intel_sdvo_connector *connector)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.base.dev);

	intel_attach_force_audio_property(&connector->base.base);
	if (INTEL_GEN(dev_priv) >= 4 && IS_MOBILE(dev_priv)) {
		intel_attach_broadcast_rgb_property(&connector->base.base);
	}
	intel_attach_aspect_ratio_property(&connector->base.base);
	connector->base.base.state->picture_aspect_ratio = HDMI_PICTURE_ASPECT_NONE;
}