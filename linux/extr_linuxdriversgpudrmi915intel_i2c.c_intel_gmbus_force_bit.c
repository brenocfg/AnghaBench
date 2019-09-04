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
struct intel_gmbus {int force_bit; struct drm_i915_private* dev_priv; } ;
struct i2c_adapter {int /*<<< orphan*/  name; } ;
struct drm_i915_private {int /*<<< orphan*/  gmbus_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct intel_gmbus* to_intel_gmbus (struct i2c_adapter*) ; 

void intel_gmbus_force_bit(struct i2c_adapter *adapter, bool force_bit)
{
	struct intel_gmbus *bus = to_intel_gmbus(adapter);
	struct drm_i915_private *dev_priv = bus->dev_priv;

	mutex_lock(&dev_priv->gmbus_mutex);

	bus->force_bit += force_bit ? 1 : -1;
	DRM_DEBUG_KMS("%sabling bit-banging on %s. force bit now %d\n",
		      force_bit ? "en" : "dis", adapter->name,
		      bus->force_bit);

	mutex_unlock(&dev_priv->gmbus_mutex);
}