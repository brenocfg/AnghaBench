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
struct samsung_laptop {TYPE_1__* config; } ;
struct sabi_commands {int /*<<< orphan*/  set_backlight; } ;
struct TYPE_4__ {scalar_t__ power; int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_2__ props; } ;
struct TYPE_3__ {struct sabi_commands commands; } ;

/* Variables and functions */
 scalar_t__ FB_BLANK_UNBLANK ; 
 struct samsung_laptop* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  sabi_set_commandb (struct samsung_laptop*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_brightness (struct samsung_laptop*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_status(struct backlight_device *bd)
{
	struct samsung_laptop *samsung = bl_get_data(bd);
	const struct sabi_commands *commands = &samsung->config->commands;

	set_brightness(samsung, bd->props.brightness);

	if (bd->props.power == FB_BLANK_UNBLANK)
		sabi_set_commandb(samsung, commands->set_backlight, 1);
	else
		sabi_set_commandb(samsung, commands->set_backlight, 0);

	return 0;
}