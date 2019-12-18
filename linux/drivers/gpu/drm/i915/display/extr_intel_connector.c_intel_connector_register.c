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
struct intel_connector {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ i915_inject_probe_failure (int /*<<< orphan*/ ) ; 
 int intel_backlight_device_register (struct intel_connector*) ; 
 int /*<<< orphan*/  intel_backlight_device_unregister (struct intel_connector*) ; 
 int /*<<< orphan*/  to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

int intel_connector_register(struct drm_connector *connector)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);
	int ret;

	ret = intel_backlight_device_register(intel_connector);
	if (ret)
		goto err;

	if (i915_inject_probe_failure(to_i915(connector->dev))) {
		ret = -EFAULT;
		goto err_backlight;
	}

	return 0;

err_backlight:
	intel_backlight_device_unregister(intel_connector);
err:
	return ret;
}