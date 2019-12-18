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
struct drm_psb_private {int backlight_enabled; TYPE_1__* ops; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {int (* backlight_init ) (struct drm_device*) ;} ;

/* Variables and functions */
 int stub1 (struct drm_device*) ; 

int gma_backlight_init(struct drm_device *dev)
{
#ifdef CONFIG_BACKLIGHT_CLASS_DEVICE
	struct drm_psb_private *dev_priv = dev->dev_private;
	dev_priv->backlight_enabled = true;
	return dev_priv->ops->backlight_init(dev);
#else
	return 0;
#endif
}