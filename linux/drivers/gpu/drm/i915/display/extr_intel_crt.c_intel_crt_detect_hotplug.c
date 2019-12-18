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
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_HOTPLUG_FORCE_DETECT ; 
 int /*<<< orphan*/  CRT_HOTPLUG_INT_STATUS ; 
 int CRT_HOTPLUG_MONITOR_MASK ; 
 int CRT_HOTPLUG_MONITOR_NONE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_G45 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PORT_HOTPLUG_EN ; 
 int /*<<< orphan*/  PORT_HOTPLUG_STAT ; 
 int /*<<< orphan*/  i915_hotplug_interrupt_update (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int intel_ironlake_crt_detect_hotplug (struct drm_connector*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int valleyview_crt_detect_hotplug (struct drm_connector*) ; 

__attribute__((used)) static bool intel_crt_detect_hotplug(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 stat;
	bool ret = false;
	int i, tries = 0;

	if (HAS_PCH_SPLIT(dev_priv))
		return intel_ironlake_crt_detect_hotplug(connector);

	if (IS_VALLEYVIEW(dev_priv))
		return valleyview_crt_detect_hotplug(connector);

	/*
	 * On 4 series desktop, CRT detect sequence need to be done twice
	 * to get a reliable result.
	 */

	if (IS_G45(dev_priv))
		tries = 2;
	else
		tries = 1;

	for (i = 0; i < tries ; i++) {
		/* turn on the FORCE_DETECT */
		i915_hotplug_interrupt_update(dev_priv,
					      CRT_HOTPLUG_FORCE_DETECT,
					      CRT_HOTPLUG_FORCE_DETECT);
		/* wait for FORCE_DETECT to go off */
		if (intel_de_wait_for_clear(dev_priv, PORT_HOTPLUG_EN,
					    CRT_HOTPLUG_FORCE_DETECT, 1000))
			DRM_DEBUG_KMS("timed out waiting for FORCE_DETECT to go off");
	}

	stat = I915_READ(PORT_HOTPLUG_STAT);
	if ((stat & CRT_HOTPLUG_MONITOR_MASK) != CRT_HOTPLUG_MONITOR_NONE)
		ret = true;

	/* clear the interrupt we just generated, if any */
	I915_WRITE(PORT_HOTPLUG_STAT, CRT_HOTPLUG_INT_STATUS);

	i915_hotplug_interrupt_update(dev_priv, CRT_HOTPLUG_FORCE_DETECT, 0);

	return ret;
}