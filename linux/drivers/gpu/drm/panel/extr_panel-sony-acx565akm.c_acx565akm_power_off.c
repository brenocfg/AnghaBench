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
struct acx565akm_panel {int enabled; int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  acx565akm_set_display_state (struct acx565akm_panel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acx565akm_set_sleep_mode (struct acx565akm_panel*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void acx565akm_power_off(struct acx565akm_panel *lcd)
{
	if (!lcd->enabled)
		return;

	acx565akm_set_display_state(lcd, 0);
	acx565akm_set_sleep_mode(lcd, 1);
	lcd->enabled = false;
	/*
	 * We have to provide PCLK,HS,VS signals for 2 frames (worst case
	 * ~50msec) after sending the sleep in command and asserting the
	 * reset signal. We probably could assert the reset w/o the delay
	 * but we still delay to avoid possible artifacts. (7.6.1)
	 */
	msleep(50);

	gpiod_set_value(lcd->reset_gpio, 0);

	/* FIXME need to tweak this delay */
	msleep(100);
}