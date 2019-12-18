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
struct lm3639_chip_data {TYPE_1__* bled; int /*<<< orphan*/  cdev_flash; int /*<<< orphan*/  cdev_torch; int /*<<< orphan*/  regmap; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ENABLE ; 
 int /*<<< orphan*/  dev_attr_bled_mode ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lm3639_chip_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lm3639_remove(struct i2c_client *client)
{
	struct lm3639_chip_data *pchip = i2c_get_clientdata(client);

	regmap_write(pchip->regmap, REG_ENABLE, 0x00);

	led_classdev_unregister(&pchip->cdev_torch);
	led_classdev_unregister(&pchip->cdev_flash);
	if (pchip->bled)
		device_remove_file(&(pchip->bled->dev), &dev_attr_bled_mode);
	return 0;
}