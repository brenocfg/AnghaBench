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
struct lp3944_platform_data {int leds_size; } ;
struct lp3944_data {TYPE_1__* leds; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  ldev; } ;

/* Variables and functions */
#define  LP3944_LED_TYPE_LED 130 
#define  LP3944_LED_TYPE_LED_INVERTED 129 
#define  LP3944_LED_TYPE_NONE 128 
 struct lp3944_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct lp3944_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp3944_remove(struct i2c_client *client)
{
	struct lp3944_platform_data *pdata = dev_get_platdata(&client->dev);
	struct lp3944_data *data = i2c_get_clientdata(client);
	int i;

	for (i = 0; i < pdata->leds_size; i++)
		switch (data->leds[i].type) {
		case LP3944_LED_TYPE_LED:
		case LP3944_LED_TYPE_LED_INVERTED:
			led_classdev_unregister(&data->leds[i].ldev);
			break;

		case LP3944_LED_TYPE_NONE:
		default:
			break;
		}

	return 0;
}