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
struct ov7670_info {void* resetb_gpio; void* pwdn_gpio; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 void* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ov7670_init_gpio(struct i2c_client *client, struct ov7670_info *info)
{
	info->pwdn_gpio = devm_gpiod_get_optional(&client->dev, "powerdown",
			GPIOD_OUT_LOW);
	if (IS_ERR(info->pwdn_gpio)) {
		dev_info(&client->dev, "can't get %s GPIO\n", "powerdown");
		return PTR_ERR(info->pwdn_gpio);
	}

	info->resetb_gpio = devm_gpiod_get_optional(&client->dev, "reset",
			GPIOD_OUT_LOW);
	if (IS_ERR(info->resetb_gpio)) {
		dev_info(&client->dev, "can't get %s GPIO\n", "reset");
		return PTR_ERR(info->resetb_gpio);
	}

	usleep_range(3000, 5000);

	return 0;
}