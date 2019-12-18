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
typedef  int u32 ;
struct TYPE_2__ {int saveBLC_PWM_CTL; } ;
struct drm_psb_private {TYPE_1__ regs; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int BACKLIGHT_DUTY_CYCLE_MASK ; 
 int BACKLIGHT_DUTY_CYCLE_SHIFT ; 
 int /*<<< orphan*/  BLC_PWM_CTL ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 

__attribute__((used)) static void psb_intel_lvds_set_backlight(struct drm_device *dev, int level)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	u32 blc_pwm_ctl;

	if (gma_power_begin(dev, false)) {
		blc_pwm_ctl = REG_READ(BLC_PWM_CTL);
		blc_pwm_ctl &= ~BACKLIGHT_DUTY_CYCLE_MASK;
		REG_WRITE(BLC_PWM_CTL,
				(blc_pwm_ctl |
				(level << BACKLIGHT_DUTY_CYCLE_SHIFT)));
		dev_priv->regs.saveBLC_PWM_CTL = (blc_pwm_ctl |
					(level << BACKLIGHT_DUTY_CYCLE_SHIFT));
		gma_power_end(dev);
	} else {
		blc_pwm_ctl = dev_priv->regs.saveBLC_PWM_CTL &
				~BACKLIGHT_DUTY_CYCLE_MASK;
		dev_priv->regs.saveBLC_PWM_CTL = (blc_pwm_ctl |
					(level << BACKLIGHT_DUTY_CYCLE_SHIFT));
	}
}