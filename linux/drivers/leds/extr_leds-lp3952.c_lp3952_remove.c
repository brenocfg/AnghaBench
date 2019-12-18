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
struct lp3952_led_array {int /*<<< orphan*/  enable_gpio; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP3952_LED_ALL ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lp3952_led_array* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lp3952_on_off (struct lp3952_led_array*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lp3952_remove(struct i2c_client *client)
{
	struct lp3952_led_array *priv;

	priv = i2c_get_clientdata(client);
	lp3952_on_off(priv, LP3952_LED_ALL, false);
	gpiod_set_value(priv->enable_gpio, 0);

	return 0;
}