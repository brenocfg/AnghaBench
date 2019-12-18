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
struct vmw_private {scalar_t__ hotplug_mode_update_property; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_PROP_IMMUTABLE ; 
 scalar_t__ drm_property_create_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmw_kms_create_hotplug_mode_update_property(struct vmw_private *dev_priv)
{
	if (dev_priv->hotplug_mode_update_property)
		return;

	dev_priv->hotplug_mode_update_property =
		drm_property_create_range(dev_priv->dev,
					  DRM_MODE_PROP_IMMUTABLE,
					  "hotplug_mode_update", 0, 1);

	if (!dev_priv->hotplug_mode_update_property)
		return;

}