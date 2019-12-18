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
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct blinkm_data {int next_red; int next_green; int next_blue; int next_hue; int next_saturation; int next_brightness; TYPE_1__* blinkm_leds; } ;
struct TYPE_3__ {int /*<<< orphan*/  led_cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLM_FADE_HSB ; 
 int /*<<< orphan*/  BLM_FADE_RGB ; 
 int /*<<< orphan*/  BLM_GO_RGB ; 
 int /*<<< orphan*/  blinkm_group ; 
 int blinkm_transfer_hw (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct blinkm_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int blinkm_remove(struct i2c_client *client)
{
	struct blinkm_data *data = i2c_get_clientdata(client);
	int ret = 0;
	int i;

	/* make sure no workqueue entries are pending */
	for (i = 0; i < 3; i++)
		led_classdev_unregister(&data->blinkm_leds[i].led_cdev);

	/* reset rgb */
	data->next_red = 0x00;
	data->next_green = 0x00;
	data->next_blue = 0x00;
	ret = blinkm_transfer_hw(client, BLM_FADE_RGB);
	if (ret < 0)
		dev_err(&client->dev, "Failure in blinkm_remove ignored. Continuing.\n");

	/* reset hsb */
	data->next_hue = 0x00;
	data->next_saturation = 0x00;
	data->next_brightness = 0x00;
	ret = blinkm_transfer_hw(client, BLM_FADE_HSB);
	if (ret < 0)
		dev_err(&client->dev, "Failure in blinkm_remove ignored. Continuing.\n");

	/* red fade to off */
	data->next_red = 0xff;
	ret = blinkm_transfer_hw(client, BLM_GO_RGB);
	if (ret < 0)
		dev_err(&client->dev, "Failure in blinkm_remove ignored. Continuing.\n");

	/* off */
	data->next_red = 0x00;
	ret = blinkm_transfer_hw(client, BLM_FADE_RGB);
	if (ret < 0)
		dev_err(&client->dev, "Failure in blinkm_remove ignored. Continuing.\n");

	sysfs_remove_group(&client->dev.kobj, &blinkm_group);
	return 0;
}