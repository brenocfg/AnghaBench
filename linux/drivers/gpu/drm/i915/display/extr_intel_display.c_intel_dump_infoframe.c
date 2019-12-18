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
typedef  union hdmi_infoframe {int dummy; } hdmi_infoframe ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int DRM_UT_KMS ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int drm_debug ; 
 int /*<<< orphan*/  hdmi_infoframe_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union hdmi_infoframe const*) ; 

__attribute__((used)) static void
intel_dump_infoframe(struct drm_i915_private *dev_priv,
		     const union hdmi_infoframe *frame)
{
	if ((drm_debug & DRM_UT_KMS) == 0)
		return;

	hdmi_infoframe_log(KERN_DEBUG, dev_priv->drm.dev, frame);
}