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
typedef  int /*<<< orphan*/  u8 ;
struct lp855x {scalar_t__ mode; TYPE_1__* cfg; } ;
struct TYPE_4__ {int brightness; int state; int /*<<< orphan*/  max_brightness; } ;
struct backlight_device {TYPE_2__ props; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg_brightness; } ;

/* Variables and functions */
 int BL_CORE_FBBLANK ; 
 int BL_CORE_SUSPENDED ; 
 scalar_t__ PWM_BASED ; 
 scalar_t__ REGISTER_BASED ; 
 struct lp855x* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  lp855x_pwm_ctrl (struct lp855x*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp855x_write_byte (struct lp855x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp855x_bl_update_status(struct backlight_device *bl)
{
	struct lp855x *lp = bl_get_data(bl);
	int brightness = bl->props.brightness;

	if (bl->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	if (lp->mode == PWM_BASED)
		lp855x_pwm_ctrl(lp, brightness, bl->props.max_brightness);
	else if (lp->mode == REGISTER_BASED)
		lp855x_write_byte(lp, lp->cfg->reg_brightness, (u8)brightness);

	return 0;
}