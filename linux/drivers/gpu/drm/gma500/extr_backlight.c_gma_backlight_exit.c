#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_psb_private {TYPE_2__* backlight_device; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_4__ {scalar_t__ brightness; } ;
struct TYPE_5__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  backlight_update_status (TYPE_2__*) ; 

void gma_backlight_exit(struct drm_device *dev)
{
#ifdef CONFIG_BACKLIGHT_CLASS_DEVICE
	struct drm_psb_private *dev_priv = dev->dev_private;
	if (dev_priv->backlight_device) {
		dev_priv->backlight_device->props.brightness = 0;
		backlight_update_status(dev_priv->backlight_device);
		backlight_device_unregister(dev_priv->backlight_device);
	}
#endif
}