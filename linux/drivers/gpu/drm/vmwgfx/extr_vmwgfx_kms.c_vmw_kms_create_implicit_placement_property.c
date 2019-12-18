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
struct vmw_private {int /*<<< orphan*/  dev; scalar_t__ implicit_placement_property; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_PROP_IMMUTABLE ; 
 scalar_t__ drm_property_create_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

void
vmw_kms_create_implicit_placement_property(struct vmw_private *dev_priv)
{
	if (dev_priv->implicit_placement_property)
		return;

	dev_priv->implicit_placement_property =
		drm_property_create_range(dev_priv->dev,
					  DRM_MODE_PROP_IMMUTABLE,
					  "implicit_placement", 0, 1);
}