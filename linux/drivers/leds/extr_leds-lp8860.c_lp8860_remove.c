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
struct lp8860_led {int /*<<< orphan*/  lock; TYPE_1__* client; scalar_t__ regulator; scalar_t__ enable_gpio; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpiod_direction_output (scalar_t__,int /*<<< orphan*/ ) ; 
 struct lp8860_led* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int regulator_disable (scalar_t__) ; 

__attribute__((used)) static int lp8860_remove(struct i2c_client *client)
{
	struct lp8860_led *led = i2c_get_clientdata(client);
	int ret;

	if (led->enable_gpio)
		gpiod_direction_output(led->enable_gpio, 0);

	if (led->regulator) {
		ret = regulator_disable(led->regulator);
		if (ret)
			dev_err(&led->client->dev,
				"Failed to disable regulator\n");
	}

	mutex_destroy(&led->lock);

	return 0;
}