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
typedef  int u32 ;
struct intel_crt {int /*<<< orphan*/  adpa_reg; scalar_t__ force_hotplug_required; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int ADPA_CRT_HOTPLUG_FORCE_TRIGGER ; 
 int ADPA_CRT_HOTPLUG_MONITOR_MASK ; 
 int ADPA_DAC_ENABLE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct intel_crt* intel_attached_crt (struct drm_connector*) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static bool intel_ironlake_crt_detect_hotplug(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct intel_crt *crt = intel_attached_crt(connector);
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 adpa;
	bool ret;

	/* The first time through, trigger an explicit detection cycle */
	if (crt->force_hotplug_required) {
		bool turn_off_dac = HAS_PCH_SPLIT(dev_priv);
		u32 save_adpa;

		crt->force_hotplug_required = 0;

		save_adpa = adpa = I915_READ(crt->adpa_reg);
		DRM_DEBUG_KMS("trigger hotplug detect cycle: adpa=0x%x\n", adpa);

		adpa |= ADPA_CRT_HOTPLUG_FORCE_TRIGGER;
		if (turn_off_dac)
			adpa &= ~ADPA_DAC_ENABLE;

		I915_WRITE(crt->adpa_reg, adpa);

		if (intel_de_wait_for_clear(dev_priv,
					    crt->adpa_reg,
					    ADPA_CRT_HOTPLUG_FORCE_TRIGGER,
					    1000))
			DRM_DEBUG_KMS("timed out waiting for FORCE_TRIGGER");

		if (turn_off_dac) {
			I915_WRITE(crt->adpa_reg, save_adpa);
			POSTING_READ(crt->adpa_reg);
		}
	}

	/* Check the status to see if both blue and green are on now */
	adpa = I915_READ(crt->adpa_reg);
	if ((adpa & ADPA_CRT_HOTPLUG_MONITOR_MASK) != 0)
		ret = true;
	else
		ret = false;
	DRM_DEBUG_KMS("ironlake hotplug adpa=0x%x, result %d\n", adpa, ret);

	return ret;
}