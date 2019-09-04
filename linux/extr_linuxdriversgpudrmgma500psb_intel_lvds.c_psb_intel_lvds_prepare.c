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
struct psb_intel_mode_device {int saveBLC_PWM_CTL; int backlight_duty_cycle; } ;
struct drm_psb_private {struct psb_intel_mode_device mode_dev; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int BACKLIGHT_DUTY_CYCLE_MASK ; 
 int /*<<< orphan*/  BLC_PWM_CTL ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 
 int /*<<< orphan*/  psb_intel_lvds_set_power (struct drm_device*,int) ; 

__attribute__((used)) static void psb_intel_lvds_prepare(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct psb_intel_mode_device *mode_dev = &dev_priv->mode_dev;

	if (!gma_power_begin(dev, true))
		return;

	mode_dev->saveBLC_PWM_CTL = REG_READ(BLC_PWM_CTL);
	mode_dev->backlight_duty_cycle = (mode_dev->saveBLC_PWM_CTL &
					  BACKLIGHT_DUTY_CYCLE_MASK);

	psb_intel_lvds_set_power(dev, false);

	gma_power_end(dev);
}