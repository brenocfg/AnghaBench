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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int brightness; int power; int fb_blank; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ CRVML_BACKLIGHT_OFF ; 
 scalar_t__ CRVML_PANEL_PORT ; 
 int FB_BLANK_POWERDOWN ; 
 int FB_BLANK_UNBLANK ; 
 scalar_t__ gpio_bar ; 
 scalar_t__ inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cr_backlight_set_intensity(struct backlight_device *bd)
{
	int intensity = bd->props.brightness;
	u32 addr = gpio_bar + CRVML_PANEL_PORT;
	u32 cur = inl(addr);

	if (bd->props.power == FB_BLANK_UNBLANK)
		intensity = FB_BLANK_UNBLANK;
	if (bd->props.fb_blank == FB_BLANK_UNBLANK)
		intensity = FB_BLANK_UNBLANK;
	if (bd->props.power == FB_BLANK_POWERDOWN)
		intensity = FB_BLANK_POWERDOWN;
	if (bd->props.fb_blank == FB_BLANK_POWERDOWN)
		intensity = FB_BLANK_POWERDOWN;

	if (intensity == FB_BLANK_UNBLANK) { /* FULL ON */
		cur &= ~CRVML_BACKLIGHT_OFF;
		outl(cur, addr);
	} else if (intensity == FB_BLANK_POWERDOWN) { /* OFF */
		cur |= CRVML_BACKLIGHT_OFF;
		outl(cur, addr);
	} /* anything else, don't bother */

	return 0;
}