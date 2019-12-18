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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 struct gpio_desc* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (struct gpio_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tvp5150_init(struct i2c_client *c)
{
	struct gpio_desc *pdn_gpio;
	struct gpio_desc *reset_gpio;

	pdn_gpio = devm_gpiod_get_optional(&c->dev, "pdn", GPIOD_OUT_HIGH);
	if (IS_ERR(pdn_gpio))
		return PTR_ERR(pdn_gpio);

	if (pdn_gpio) {
		gpiod_set_value_cansleep(pdn_gpio, 0);
		/* Delay time between power supplies active and reset */
		msleep(20);
	}

	reset_gpio = devm_gpiod_get_optional(&c->dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(reset_gpio))
		return PTR_ERR(reset_gpio);

	if (reset_gpio) {
		/* RESETB pulse duration */
		ndelay(500);
		gpiod_set_value_cansleep(reset_gpio, 0);
		/* Delay time between end of reset to I2C active */
		usleep_range(200, 250);
	}

	return 0;
}