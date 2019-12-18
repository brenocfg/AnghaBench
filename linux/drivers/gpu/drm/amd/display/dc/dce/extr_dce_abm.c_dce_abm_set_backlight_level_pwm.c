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
struct dce_abm {int dummy; } ;
struct abm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOG_BACKLIGHT (char*,unsigned int,unsigned int) ; 
 struct dce_abm* TO_DCE_ABM (struct abm*) ; 
 int /*<<< orphan*/  dmcu_set_backlight_level (struct dce_abm*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  driver_set_backlight_level (struct dce_abm*,unsigned int) ; 

__attribute__((used)) static bool dce_abm_set_backlight_level_pwm(
		struct abm *abm,
		unsigned int backlight_pwm_u16_16,
		unsigned int frame_ramp,
		unsigned int controller_id,
		bool use_smooth_brightness)
{
	struct dce_abm *abm_dce = TO_DCE_ABM(abm);

	DC_LOG_BACKLIGHT("New Backlight level: %d (0x%X)\n",
			backlight_pwm_u16_16, backlight_pwm_u16_16);

	/* If DMCU is in reset state, DMCU is uninitialized */
	if (use_smooth_brightness)
		dmcu_set_backlight_level(abm_dce,
				backlight_pwm_u16_16,
				frame_ramp,
				controller_id);
	else
		driver_set_backlight_level(abm_dce, backlight_pwm_u16_16);

	return true;
}