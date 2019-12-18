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
struct drm_psb_private {TYPE_1__* lvds_bl; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ BLC_I2C_TYPE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  psb_lvds_i2c_set_brightness (struct drm_device*,int) ; 
 int /*<<< orphan*/  psb_lvds_pwm_set_brightness (struct drm_device*,int) ; 

void psb_intel_lvds_set_brightness(struct drm_device *dev, int level)
{
	struct drm_psb_private *dev_priv = dev->dev_private;

	dev_dbg(dev->dev, "backlight level is %d\n", level);

	if (!dev_priv->lvds_bl) {
		dev_err(dev->dev, "NO LVDS backlight info\n");
		return;
	}

	if (dev_priv->lvds_bl->type == BLC_I2C_TYPE)
		psb_lvds_i2c_set_brightness(dev, level);
	else
		psb_lvds_pwm_set_brightness(dev, level);
}