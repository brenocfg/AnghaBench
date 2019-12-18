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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ vbt; } ;
struct drm_psb_private {int child_dev_num; TYPE_1__ opregion; struct child_device_config* child_dev; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct child_device_config {scalar_t__ device_type; scalar_t__ addin_offset; scalar_t__ i2c_pin; } ;

/* Variables and functions */
 scalar_t__ DEVICE_TYPE_INT_LFP ; 
 scalar_t__ DEVICE_TYPE_LFP ; 

__attribute__((used)) static bool lvds_is_present_in_vbt(struct drm_device *dev,
				   u8 *i2c_pin)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	int i;

	if (!dev_priv->child_dev_num)
		return true;

	for (i = 0; i < dev_priv->child_dev_num; i++) {
		struct child_device_config *child = dev_priv->child_dev + i;

		/* If the device type is not LFP, continue.
		 * We have to check both the new identifiers as well as the
		 * old for compatibility with some BIOSes.
		 */
		if (child->device_type != DEVICE_TYPE_INT_LFP &&
		    child->device_type != DEVICE_TYPE_LFP)
			continue;

		if (child->i2c_pin)
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