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
struct TYPE_2__ {scalar_t__ name; } ;
struct tca6507_led {TYPE_1__ led_cdev; } ;
struct tca6507_chip {int /*<<< orphan*/  work; struct tca6507_led* leds; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int NUM_LEDS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct tca6507_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  tca6507_remove_gpio (struct tca6507_chip*) ; 

__attribute__((used)) static int tca6507_remove(struct i2c_client *client)
{
	int i;
	struct tca6507_chip *tca = i2c_get_clientdata(client);
	struct tca6507_led *tca_leds = tca->leds;

	for (i = 0; i < NUM_LEDS; i++) {
		if (tca_leds[i].led_cdev.name)
			led_classdev_unregister(&tca_leds[i].led_cdev);
	}
	tca6507_remove_gpio(tca);
	cancel_work_sync(&tca->work);

	return 0;
}