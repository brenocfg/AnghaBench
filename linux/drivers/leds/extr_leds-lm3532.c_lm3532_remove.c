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
struct lm3532_data {scalar_t__ enable_gpio; int /*<<< orphan*/  lock; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_direction_output (scalar_t__,int /*<<< orphan*/ ) ; 
 struct lm3532_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm3532_remove(struct i2c_client *client)
{
	struct lm3532_data *drvdata = i2c_get_clientdata(client);

	mutex_destroy(&drvdata->lock);

	if (drvdata->enable_gpio)
		gpiod_direction_output(drvdata->enable_gpio, 0);

	return 0;
}