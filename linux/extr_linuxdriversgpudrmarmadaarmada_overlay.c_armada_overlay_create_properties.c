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
struct drm_device {struct armada_private* dev_private; } ;
struct armada_private {void* colorkey_prop; void* saturation_prop; void* contrast_prop; void* brightness_prop; int /*<<< orphan*/  colorkey_mode_prop; void* colorkey_alpha_prop; void* colorkey_val_prop; void* colorkey_max_prop; void* colorkey_min_prop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  armada_drm_colorkey_enum_list ; 
 int /*<<< orphan*/  drm_property_create_enum (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* drm_property_create_range (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int armada_overlay_create_properties(struct drm_device *dev)
{
	struct armada_private *priv = dev->dev_private;

	if (priv->colorkey_prop)
		return 0;

	priv->colorkey_prop = drm_property_create_range(dev, 0,
				"colorkey", 0, 0xffffff);
	priv->colorkey_min_prop = drm_property_create_range(dev, 0,
				"colorkey_min", 0, 0xffffff);
	priv->colorkey_max_prop = drm_property_create_range(dev, 0,
				"colorkey_max", 0, 0xffffff);
	priv->colorkey_val_prop = drm_property_create_range(dev, 0,
				"colorkey_val", 0, 0xffffff);
	priv->colorkey_alpha_prop = drm_property_create_range(dev, 0,
				"colorkey_alpha", 0, 0xffffff);
	priv->colorkey_mode_prop = drm_property_create_enum(dev, 0,
				"colorkey_mode",
				armada_drm_colorkey_enum_list,
				ARRAY_SIZE(armada_drm_colorkey_enum_list));
	priv->brightness_prop = drm_property_create_range(dev, 0,
				"brightness", 0, 256 + 255);
	priv->contrast_prop = drm_property_create_range(dev, 0,
				"contrast", 0, 0x7fff);
	priv->saturation_prop = drm_property_create_range(dev, 0,
				"saturation", 0, 0x7fff);

	if (!priv->colorkey_prop)
		return -ENOMEM;

	return 0;
}