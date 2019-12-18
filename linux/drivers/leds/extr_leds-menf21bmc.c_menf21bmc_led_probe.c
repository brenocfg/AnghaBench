#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct i2c_client {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_3__ cdev; struct i2c_client* i2c_client; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int devm_led_classdev_register (TYPE_2__*,TYPE_3__*) ; 
 TYPE_1__* leds ; 
 int /*<<< orphan*/  menf21bmc_led_set ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int menf21bmc_led_probe(struct platform_device *pdev)
{
	int i;
	int ret;
	struct i2c_client *i2c_client = to_i2c_client(pdev->dev.parent);

	for (i = 0; i < ARRAY_SIZE(leds); i++) {
		leds[i].cdev.name = leds[i].name;
		leds[i].cdev.brightness_set = menf21bmc_led_set;
		leds[i].i2c_client = i2c_client;
		ret = devm_led_classdev_register(&pdev->dev, &leds[i].cdev);
		if (ret < 0) {
			dev_err(&pdev->dev, "failed to register LED device\n");
			return ret;
		}
	}
	dev_info(&pdev->dev, "MEN 140F21P00 BMC LED device enabled\n");

	return 0;

}