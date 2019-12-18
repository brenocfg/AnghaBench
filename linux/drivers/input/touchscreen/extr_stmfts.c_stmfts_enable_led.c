#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  brightness_get; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  brightness; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  name; } ;
struct stmfts_data {int /*<<< orphan*/  ledvdd; TYPE_2__ led_cdev; TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  LED_ON ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMFTS_DEV_NAME ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_regulator_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmfts_brightness_get ; 
 int /*<<< orphan*/  stmfts_brightness_set ; 

__attribute__((used)) static int stmfts_enable_led(struct stmfts_data *sdata)
{
	int err;

	/* get the regulator for powering the leds on */
	sdata->ledvdd = devm_regulator_get(&sdata->client->dev, "ledvdd");
	if (IS_ERR(sdata->ledvdd))
		return PTR_ERR(sdata->ledvdd);

	sdata->led_cdev.name = STMFTS_DEV_NAME;
	sdata->led_cdev.max_brightness = LED_ON;
	sdata->led_cdev.brightness = LED_OFF;
	sdata->led_cdev.brightness_set_blocking = stmfts_brightness_set;
	sdata->led_cdev.brightness_get = stmfts_brightness_get;

	err = devm_led_classdev_register(&sdata->client->dev, &sdata->led_cdev);
	if (err) {
		devm_regulator_put(sdata->ledvdd);
		return err;
	}

	return 0;
}