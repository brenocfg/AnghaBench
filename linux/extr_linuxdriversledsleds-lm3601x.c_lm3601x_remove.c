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
struct lm3601x_led {int /*<<< orphan*/  regmap; int /*<<< orphan*/  lock; int /*<<< orphan*/  fled_cdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3601X_ENABLE_MASK ; 
 int /*<<< orphan*/  LM3601X_ENABLE_REG ; 
 int /*<<< orphan*/  LM3601X_MODE_STANDBY ; 
 struct lm3601x_led* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  led_classdev_flash_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3601x_remove(struct i2c_client *client)
{
	struct lm3601x_led *led = i2c_get_clientdata(client);

	led_classdev_flash_unregister(&led->fled_cdev);
	mutex_destroy(&led->lock);

	return regmap_update_bits(led->regmap, LM3601X_ENABLE_REG,
			   LM3601X_ENABLE_MASK,
			   LM3601X_MODE_STANDBY);
}