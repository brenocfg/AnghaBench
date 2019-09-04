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
struct drm_device {int dummy; } ;

/* Variables and functions */

void gma_backlight_set(struct drm_device *dev, int v)
{
#ifdef CONFIG_BACKLIGHT_CLASS_DEVICE
	struct drm_psb_private *dev_priv = dev->dev_private;
	dev_priv->backlight_level = v;
	if (dev_priv->backlight_device && dev_priv->backlight_enabled) {
		dev_priv->backlight_device->props.brightness = v;
		do_gma_backlight_set(dev);
	}
#endif	
}