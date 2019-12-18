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
struct acx565akm_panel {int enabled; int /*<<< orphan*/  backlight; int /*<<< orphan*/  cabc_mode; TYPE_1__* spi; int /*<<< orphan*/  reset_gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int acx565akm_bl_update_status_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acx565akm_set_cabc_mode (struct acx565akm_panel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acx565akm_set_display_state (struct acx565akm_panel*,int) ; 
 int /*<<< orphan*/  acx565akm_set_sleep_mode (struct acx565akm_panel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int acx565akm_power_on(struct acx565akm_panel *lcd)
{
	/*FIXME tweak me */
	msleep(50);

	gpiod_set_value(lcd->reset_gpio, 1);

	if (lcd->enabled) {
		dev_dbg(&lcd->spi->dev, "panel already enabled\n");
		return 0;
	}

	/*
	 * We have to meet all the following delay requirements:
	 * 1. tRW: reset pulse width 10usec (7.12.1)
	 * 2. tRT: reset cancel time 5msec (7.12.1)
	 * 3. Providing PCLK,HS,VS signals for 2 frames = ~50msec worst
	 *    case (7.6.2)
	 * 4. 120msec before the sleep out command (7.12.1)
	 */
	msleep(120);

	acx565akm_set_sleep_mode(lcd, 0);
	lcd->enabled = true;

	/* 5msec between sleep out and the next command. (8.2.16) */
	usleep_range(5000, 10000);
	acx565akm_set_display_state(lcd, 1);
	acx565akm_set_cabc_mode(lcd, lcd->cabc_mode);

	return acx565akm_bl_update_status_locked(lcd->backlight);
}