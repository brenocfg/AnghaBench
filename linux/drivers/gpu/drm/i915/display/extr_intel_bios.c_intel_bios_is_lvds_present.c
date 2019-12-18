#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ vbt; } ;
struct TYPE_4__ {int child_dev_num; struct child_device_config* child_dev; } ;
struct drm_i915_private {TYPE_1__ opregion; TYPE_2__ vbt; } ;
struct child_device_config {scalar_t__ device_type; scalar_t__ addin_offset; int /*<<< orphan*/  i2c_pin; } ;

/* Variables and functions */
 scalar_t__ DEVICE_TYPE_INT_LFP ; 
 scalar_t__ DEVICE_TYPE_LFP ; 
 scalar_t__ intel_gmbus_is_valid_pin (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

bool intel_bios_is_lvds_present(struct drm_i915_private *dev_priv, u8 *i2c_pin)
{
	const struct child_device_config *child;
	int i;

	if (!dev_priv->vbt.child_dev_num)
		return true;

	for (i = 0; i < dev_priv->vbt.child_dev_num; i++) {
		child = dev_priv->vbt.child_dev + i;

		/* If the device type is not LFP, continue.
		 * We have to check both the new identifiers as well as the
		 * old for compatibility with some BIOSes.
		 */
		if (child->device_type != DEVICE_TYPE_INT_LFP &&
		    child->device_type != DEVICE_TYPE_LFP)
			continue;

		if (intel_gmbus_is_valid_pin(dev_priv, child->i2c_pin))
			*i2c_pin = child->i2c_pin;

		/* However, we cannot trust the BIOS writers to populate
		 * the VBT correctly.  Since LVDS requires additional
		 * information from AIM blocks, a non-zero addin offset is
		 * a good indicator that the LVDS is actually present.
		 */
		if (child->addin_offset)
			return true;

		/* But even then some BIOS writers perform some black magic
		 * and instantiate the device without reference to any
		 * additional data.  Trust that if the VBT was written into
		 * the OpRegion then they have validated the LVDS's existence.
		 */
		if (dev_priv->opregion.vbt)
			return true;
	}

	return false;
}