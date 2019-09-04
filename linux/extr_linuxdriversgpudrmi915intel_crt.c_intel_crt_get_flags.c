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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crt {int /*<<< orphan*/  adpa_reg; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ADPA_HSYNC_ACTIVE_HIGH ; 
 int ADPA_VSYNC_ACTIVE_HIGH ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 struct intel_crt* intel_encoder_to_crt (struct intel_encoder*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int intel_crt_get_flags(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_crt *crt = intel_encoder_to_crt(encoder);
	u32 tmp, flags = 0;

	tmp = I915_READ(crt->adpa_reg);

	if (tmp & ADPA_HSYNC_ACTIVE_HIGH)
		flags |= DRM_MODE_FLAG_PHSYNC;
	else
		flags |= DRM_MODE_FLAG_NHSYNC;

	if (tmp & ADPA_VSYNC_ACTIVE_HIGH)
		flags |= DRM_MODE_FLAG_PVSYNC;
	else
		flags |= DRM_MODE_FLAG_NVSYNC;

	return flags;
}