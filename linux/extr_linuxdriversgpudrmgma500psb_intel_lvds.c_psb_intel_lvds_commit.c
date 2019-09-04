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
struct psb_intel_mode_device {scalar_t__ backlight_duty_cycle; } ;
struct drm_psb_private {struct psb_intel_mode_device mode_dev; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ psb_intel_lvds_get_max_backlight (struct drm_device*) ; 
 int /*<<< orphan*/  psb_intel_lvds_set_power (struct drm_device*,int) ; 

__attribute__((used)) static void psb_intel_lvds_commit(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct psb_intel_mode_device *mode_dev = &dev_priv->mode_dev;

	if (mode_dev->backlight_duty_cycle == 0)
		mode_dev->backlight_duty_cycle =
		    psb_intel_lvds_get_max_backlight(dev);

	psb_intel_lvds_set_power(dev, true);
}