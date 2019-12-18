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
struct lv5207lp {int dummy; } ;
struct TYPE_2__ {int brightness; scalar_t__ power; scalar_t__ fb_blank; int state; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int BL_CORE_FBBLANK ; 
 int BL_CORE_SUSPENDED ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int LV5207LP_C10 ; 
 int LV5207LP_CKSW ; 
 int LV5207LP_CPSW ; 
 int /*<<< orphan*/  LV5207LP_CTRL1 ; 
 int /*<<< orphan*/  LV5207LP_CTRL2 ; 
 int LV5207LP_MLED4 ; 
 int LV5207LP_MSW ; 
 struct lv5207lp* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  lv5207lp_write (struct lv5207lp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lv5207lp_backlight_update_status(struct backlight_device *backlight)
{
	struct lv5207lp *lv = bl_get_data(backlight);
	int brightness = backlight->props.brightness;

	if (backlight->props.power != FB_BLANK_UNBLANK ||
	    backlight->props.fb_blank != FB_BLANK_UNBLANK ||
	    backlight->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	if (brightness) {
		lv5207lp_write(lv, LV5207LP_CTRL1,
			       LV5207LP_CPSW | LV5207LP_C10 | LV5207LP_CKSW);
		lv5207lp_write(lv, LV5207LP_CTRL2,
			       LV5207LP_MSW | LV5207LP_MLED4 |
			       (brightness - 1));
	} else {
		lv5207lp_write(lv, LV5207LP_CTRL1, 0);
		lv5207lp_write(lv, LV5207LP_CTRL2, 0);
	}

	return 0;
}