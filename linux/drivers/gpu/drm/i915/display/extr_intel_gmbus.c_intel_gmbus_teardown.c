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
struct intel_gmbus {int /*<<< orphan*/  adapter; } ;
struct drm_i915_private {struct intel_gmbus* gmbus; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct intel_gmbus*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gmbus_is_valid_pin (struct drm_i915_private*,unsigned int) ; 

void intel_gmbus_teardown(struct drm_i915_private *dev_priv)
{
	struct intel_gmbus *bus;
	unsigned int pin;

	for (pin = 0; pin < ARRAY_SIZE(dev_priv->gmbus); pin++) {
		if (!intel_gmbus_is_valid_pin(dev_priv, pin))
			continue;

		bus = &dev_priv->gmbus[pin];
		i2c_del_adapter(&bus->adapter);
	}
}