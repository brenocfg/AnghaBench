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
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int BACKLIGHT_MODULATION_FREQ_MASK ; 
 int BACKLIGHT_MODULATION_FREQ_SHIFT ; 
 int /*<<< orphan*/  BLC_PWM_CTL ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 

__attribute__((used)) static u32 psb_intel_lvds_get_max_backlight(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	u32 ret;

	if (gma_power_begin(dev, false)) {
		ret = REG_READ(BLC_PWM_CTL);
		gma_power_end(dev);
	} else /* Powered off, use the saved value */
		ret = dev_priv->regs.saveBLC_PWM_CTL;

	/* Top 15bits hold the frequency mask */
	ret = (ret &  BACKLIGHT_MODULATION_FREQ_MASK) >>
					BACKLIGHT_MODULATION_FREQ_SHIFT;

        ret *= 2;	/* Return a 16bit range as needed for setting */
        if (ret == 0)
                dev_err(dev->dev, "BL bug: Reg %08x save %08X\n",
                        REG_READ(BLC_PWM_CTL), dev_priv->regs.saveBLC_PWM_CTL);
	return ret;
}