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
struct lm3530_data {int /*<<< orphan*/  led_dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct lm3530_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lm3530_led_disable (struct lm3530_data*) ; 

__attribute__((used)) static int lm3530_remove(struct i2c_client *client)
{
	struct lm3530_data *drvdata = i2c_get_clientdata(client);

	lm3530_led_disable(drvdata);
	led_classdev_unregister(&drvdata->led_dev);
	return 0;
}