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
struct ov7740 {void* pwdn_gpio; void* resetb_gpio; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 void* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov7740_probe_dt(struct i2c_client *client,
			   struct ov7740 *ov7740)
{
	ov7740->resetb_gpio = devm_gpiod_get_optional(&client->dev, "reset",
			GPIOD_OUT_HIGH);
	if (IS_ERR(ov7740->resetb_gpio)) {
		dev_info(&client->dev, "can't get %s GPIO\n", "reset");
		return PTR_ERR(ov7740->resetb_gpio);
	}

	ov7740->pwdn_gpio = devm_gpiod_get_optional(&client->dev, "powerdown",
			GPIOD_OUT_LOW);
	if (IS_ERR(ov7740->pwdn_gpio)) {
		dev_info(&client->dev, "can't get %s GPIO\n", "powerdown");
		return PTR_ERR(ov7740->pwdn_gpio);
	}

	return 0;
}