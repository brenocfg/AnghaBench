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
struct drm_psb_private {int backlight_enabled; int /*<<< orphan*/  backlight_level; TYPE_2__* backlight_device; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  brightness; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_gma_backlight_set (struct drm_device*) ; 

void gma_backlight_enable(struct drm_device *dev)
{
#ifdef CONFIG_BACKLIGHT_CLASS_DEVICE
	struct drm_psb_private *dev_priv = dev->dev_private;
	dev_priv->backlight_enabled = true;
	if (dev_priv->backlight_device) {
		dev_priv->backlight_device->props.brightness = dev_priv->backlight_level;
		do_gma_backlight_set(dev);
	}
#endif	
}