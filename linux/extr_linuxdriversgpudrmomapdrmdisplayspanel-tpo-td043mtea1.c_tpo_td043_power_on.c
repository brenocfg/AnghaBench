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
struct panel_drv_data {int powered_on; int /*<<< orphan*/  gamma; int /*<<< orphan*/  spi; int /*<<< orphan*/  vmirror; int /*<<< orphan*/  hmirror; int /*<<< orphan*/  mode; int /*<<< orphan*/  nreset_gpio; int /*<<< orphan*/  vcc_reg; } ;

/* Variables and functions */
 int TPO_R02_MODE (int /*<<< orphan*/ ) ; 
 int TPO_R02_NCLK_RISING ; 
 int TPO_R03_VAL_NORMAL ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpo_td043_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tpo_td043_write_gamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpo_td043_write_mirror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpo_td043_power_on(struct panel_drv_data *ddata)
{
	int r;

	if (ddata->powered_on)
		return 0;

	r = regulator_enable(ddata->vcc_reg);
	if (r != 0)
		return r;

	/* wait for panel to stabilize */
	msleep(160);

	if (gpio_is_valid(ddata->nreset_gpio))
		gpio_set_value(ddata->nreset_gpio, 1);

	tpo_td043_write(ddata->spi, 2,
			TPO_R02_MODE(ddata->mode) | TPO_R02_NCLK_RISING);
	tpo_td043_write(ddata->spi, 3, TPO_R03_VAL_NORMAL);
	tpo_td043_write(ddata->spi, 0x20, 0xf0);
	tpo_td043_write(ddata->spi, 0x21, 0xf0);
	tpo_td043_write_mirror(ddata->spi, ddata->hmirror,
			ddata->vmirror);
	tpo_td043_write_gamma(ddata->spi, ddata->gamma);

	ddata->powered_on = 1;
	return 0;
}