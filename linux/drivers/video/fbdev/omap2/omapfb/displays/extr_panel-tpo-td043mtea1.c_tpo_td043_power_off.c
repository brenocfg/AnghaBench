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
struct panel_drv_data {scalar_t__ powered_on; int /*<<< orphan*/  vcc_reg; int /*<<< orphan*/  spi; int /*<<< orphan*/  nreset_gpio; } ;

/* Variables and functions */
 int TPO_R03_EN_PWM ; 
 int TPO_R03_VAL_STANDBY ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpo_td043_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void tpo_td043_power_off(struct panel_drv_data *ddata)
{
	if (!ddata->powered_on)
		return;

	tpo_td043_write(ddata->spi, 3,
			TPO_R03_VAL_STANDBY | TPO_R03_EN_PWM);

	if (gpio_is_valid(ddata->nreset_gpio))
		gpio_set_value(ddata->nreset_gpio, 0);

	/* wait for at least 2 vsyncs before cutting off power */
	msleep(50);

	tpo_td043_write(ddata->spi, 3, TPO_R03_VAL_STANDBY);

	regulator_disable(ddata->vcc_reg);

	ddata->powered_on = 0;
}