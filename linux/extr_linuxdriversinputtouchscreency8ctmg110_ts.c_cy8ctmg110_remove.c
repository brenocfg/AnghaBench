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
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct cy8ctmg110 {scalar_t__ reset_pin; scalar_t__ irq_pin; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  cy8ctmg110_power (struct cy8ctmg110*,int) ; 
 int /*<<< orphan*/  cy8ctmg110_set_sleepmode (struct cy8ctmg110*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cy8ctmg110*) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 struct cy8ctmg110* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cy8ctmg110*) ; 

__attribute__((used)) static int cy8ctmg110_remove(struct i2c_client *client)
{
	struct cy8ctmg110 *ts = i2c_get_clientdata(client);

	cy8ctmg110_set_sleepmode(ts, true);
	cy8ctmg110_power(ts, false);

	free_irq(client->irq, ts);
	input_unregister_device(ts->input);
	gpio_free(ts->irq_pin);
	if (ts->reset_pin)
		gpio_free(ts->reset_pin);
	kfree(ts);

	return 0;
}