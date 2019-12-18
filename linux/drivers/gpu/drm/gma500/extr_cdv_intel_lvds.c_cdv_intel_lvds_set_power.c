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
struct TYPE_2__ {int /*<<< orphan*/  backlight_duty_cycle; } ;
struct drm_psb_private {TYPE_1__ mode_dev; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int POWER_TARGET_ON ; 
 int /*<<< orphan*/  PP_CONTROL ; 
 int PP_ON ; 
 int /*<<< orphan*/  PP_STATUS ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdv_intel_lvds_set_backlight (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 

__attribute__((used)) static void cdv_intel_lvds_set_power(struct drm_device *dev,
				     struct drm_encoder *encoder, bool on)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	u32 pp_status;

	if (!gma_power_begin(dev, true))
		return;

	if (on) {
		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) |
			  POWER_TARGET_ON);
		do {
			pp_status = REG_READ(PP_STATUS);
		} while ((pp_status & PP_ON) == 0);

		cdv_intel_lvds_set_backlight(dev,
				dev_priv->mode_dev.backlight_duty_cycle);
	} else {
		cdv_intel_lvds_set_backlight(dev, 0);

		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) &
			  ~POWER_TARGET_ON);
		do {
			pp_status = REG_READ(PP_STATUS);
		} while (pp_status & PP_ON);
	}
	gma_power_end(dev);
}