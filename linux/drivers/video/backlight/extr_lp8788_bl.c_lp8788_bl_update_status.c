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
typedef  int u8 ;
struct lp8788_bl {int mode; int /*<<< orphan*/  lp; } ;
struct TYPE_2__ {int state; int brightness; int max_brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
typedef  enum lp8788_bl_ctrl_mode { ____Placeholder_lp8788_bl_ctrl_mode } lp8788_bl_ctrl_mode ;

/* Variables and functions */
 int BL_CORE_SUSPENDED ; 
 int /*<<< orphan*/  LP8788_BL_BRIGHTNESS ; 
 struct lp8788_bl* bl_get_data (struct backlight_device*) ; 
 scalar_t__ is_brightness_ctrl_by_pwm (int) ; 
 scalar_t__ is_brightness_ctrl_by_register (int) ; 
 int /*<<< orphan*/  lp8788_pwm_ctrl (struct lp8788_bl*,int,int) ; 
 int /*<<< orphan*/  lp8788_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lp8788_bl_update_status(struct backlight_device *bl_dev)
{
	struct lp8788_bl *bl = bl_get_data(bl_dev);
	enum lp8788_bl_ctrl_mode mode = bl->mode;

	if (bl_dev->props.state & BL_CORE_SUSPENDED)
		bl_dev->props.brightness = 0;

	if (is_brightness_ctrl_by_pwm(mode)) {
		int brt = bl_dev->props.brightness;
		int max = bl_dev->props.max_brightness;

		lp8788_pwm_ctrl(bl, brt, max);
	} else if (is_brightness_ctrl_by_register(mode)) {
		u8 brt = bl_dev->props.brightness;

		lp8788_write_byte(bl->lp, LP8788_BL_BRIGHTNESS, brt);
	}

	return 0;
}