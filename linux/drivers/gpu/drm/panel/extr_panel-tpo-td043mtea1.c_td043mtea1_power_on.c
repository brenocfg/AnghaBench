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
struct td043mtea1_panel {int powered_on; int /*<<< orphan*/  mode; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  vcc_reg; } ;

/* Variables and functions */
 int TPO_R02_MODE (int /*<<< orphan*/ ) ; 
 int TPO_R02_NCLK_RISING ; 
 int TPO_R03_VAL_NORMAL ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  td043mtea1_write (struct td043mtea1_panel*,int,int) ; 
 int /*<<< orphan*/  td043mtea1_write_gamma (struct td043mtea1_panel*) ; 
 int /*<<< orphan*/  td043mtea1_write_mirror (struct td043mtea1_panel*) ; 

__attribute__((used)) static int td043mtea1_power_on(struct td043mtea1_panel *lcd)
{
	int ret;

	if (lcd->powered_on)
		return 0;

	ret = regulator_enable(lcd->vcc_reg);
	if (ret < 0)
		return ret;

	/* Wait for the panel to stabilize. */
	msleep(160);

	gpiod_set_value(lcd->reset_gpio, 0);

	td043mtea1_write(lcd, 2, TPO_R02_MODE(lcd->mode) | TPO_R02_NCLK_RISING);
	td043mtea1_write(lcd, 3, TPO_R03_VAL_NORMAL);
	td043mtea1_write(lcd, 0x20, 0xf0);
	td043mtea1_write(lcd, 0x21, 0xf0);
	td043mtea1_write_mirror(lcd);
	td043mtea1_write_gamma(lcd);

	lcd->powered_on = true;

	return 0;
}