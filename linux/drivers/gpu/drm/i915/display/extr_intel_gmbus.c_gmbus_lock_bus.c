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
struct intel_gmbus {struct drm_i915_private* dev_priv; } ;
struct i2c_adapter {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  gmbus_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 struct intel_gmbus* to_intel_gmbus (struct i2c_adapter*) ; 

__attribute__((used)) static void gmbus_lock_bus(struct i2c_adapter *adapter,
			   unsigned int flags)
{
	struct intel_gmbus *bus = to_intel_gmbus(adapter);
	struct drm_i915_private *dev_priv = bus->dev_priv;

	mutex_lock(&dev_priv->gmbus_mutex);
}