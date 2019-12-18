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
struct lm3697 {int /*<<< orphan*/  lock; TYPE_1__* client; scalar_t__ regulator; scalar_t__ enable_gpio; int /*<<< orphan*/  regmap; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3697_CTRL_A_B_EN ; 
 int /*<<< orphan*/  LM3697_CTRL_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpiod_direction_output (scalar_t__,int /*<<< orphan*/ ) ; 
 struct lm3697* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_disable (scalar_t__) ; 

__attribute__((used)) static int lm3697_remove(struct i2c_client *client)
{
	struct lm3697 *led = i2c_get_clientdata(client);
	int ret;

	ret = regmap_update_bits(led->regmap, LM3697_CTRL_ENABLE,
				 LM3697_CTRL_A_B_EN, 0);
	if (ret) {
		dev_err(&led->client->dev, "Failed to disable the device\n");
		return ret;
	}

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