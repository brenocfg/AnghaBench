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
struct vmw_private {int /*<<< orphan*/  texture_max_height; int /*<<< orphan*/  texture_max_width; struct drm_device* dev; } ;
struct TYPE_2__ {int min_width; int min_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/ * funcs; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_create_suggested_offset_properties (struct drm_device*) ; 
 int /*<<< orphan*/  vmw_kms_create_hotplug_mode_update_property (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_kms_funcs ; 
 int vmw_kms_ldu_init_display (struct vmw_private*) ; 
 int vmw_kms_sou_init_display (struct vmw_private*) ; 
 int vmw_kms_stdu_init_display (struct vmw_private*) ; 

int vmw_kms_init(struct vmw_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	int ret;

	drm_mode_config_init(dev);
	dev->mode_config.funcs = &vmw_kms_funcs;
	dev->mode_config.min_width = 1;
	dev->mode_config.min_height = 1;
	dev->mode_config.max_width = dev_priv->texture_max_width;
	dev->mode_config.max_height = dev_priv->texture_max_height;

	drm_mode_create_suggested_offset_properties(dev);
	vmw_kms_create_hotplug_mode_update_property(dev_priv);

	ret = vmw_kms_stdu_init_display(dev_priv);
	if (ret) {
		ret = vmw_kms_sou_init_display(dev_priv);
		if (ret) /* Fallback */
			ret = vmw_kms_ldu_init_display(dev_priv);
	}

	return ret;
}