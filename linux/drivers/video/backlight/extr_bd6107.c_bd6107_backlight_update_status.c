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
struct bd6107 {TYPE_1__* pdata; } ;
struct TYPE_4__ {int brightness; scalar_t__ power; scalar_t__ fb_blank; int state; } ;
struct backlight_device {TYPE_2__ props; } ;
struct TYPE_3__ {int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD6107_LEDCNT1 ; 
 int BD6107_LEDCNT1_LEDONOFF1 ; 
 int /*<<< orphan*/  BD6107_MAINCNT1 ; 
 int /*<<< orphan*/  BD6107_PORTSEL ; 
 int BD6107_PORTSEL_LEDM (int) ; 
 int BL_CORE_FBBLANK ; 
 int BL_CORE_SUSPENDED ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  bd6107_write (struct bd6107*,int /*<<< orphan*/ ,int) ; 
 struct bd6107* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int bd6107_backlight_update_status(struct backlight_device *backlight)
{
	struct bd6107 *bd = bl_get_data(backlight);
	int brightness = backlight->props.brightness;

	if (backlight->props.power != FB_BLANK_UNBLANK ||
	    backlight->props.fb_blank != FB_BLANK_UNBLANK ||
	    backlight->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	if (brightness) {
		bd6107_write(bd, BD6107_PORTSEL, BD6107_PORTSEL_LEDM(2) |
			     BD6107_PORTSEL_LEDM(1) | BD6107_PORTSEL_LEDM(0));
		bd6107_write(bd, BD6107_MAINCNT1, brightness);
		bd6107_write(bd, BD6107_LEDCNT1, BD6107_LEDCNT1_LEDONOFF1);
	} else {
		gpio_set_value(bd->pdata->reset, 0);
		msleep(24);
		gpio_set_value(bd->pdata->reset, 1);
	}

	return 0;
}