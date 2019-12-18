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
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct asus_laptop {struct backlight_device* backlight_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_UPDATE_HOTKEY ; 
 int /*<<< orphan*/  backlight_force_update (struct backlight_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_backlight_notify(struct asus_laptop *asus)
{
	struct backlight_device *bd = asus->backlight_device;
	int old = bd->props.brightness;

	backlight_force_update(bd, BACKLIGHT_UPDATE_HOTKEY);

	return old;
}