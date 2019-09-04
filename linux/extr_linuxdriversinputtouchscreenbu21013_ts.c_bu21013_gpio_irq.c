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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct bu21013_ts_data {scalar_t__ intr_pin; int /*<<< orphan*/  touch_stopped; int /*<<< orphan*/  wait; TYPE_1__* chip; struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  touch_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PEN_DOWN_INTR ; 
 int bu21013_do_touch_report (struct bu21013_ts_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bu21013_gpio_irq(int irq, void *device_data)
{
	struct bu21013_ts_data *data = device_data;
	struct i2c_client *i2c = data->client;
	int retval;

	do {
		retval = bu21013_do_touch_report(data);
		if (retval < 0) {
			dev_err(&i2c->dev, "bu21013_do_touch_report failed\n");
			return IRQ_NONE;
		}

		data->intr_pin = gpio_get_value(data->chip->touch_pin);
		if (data->intr_pin == PEN_DOWN_INTR)
			wait_event_timeout(data->wait, data->touch_stopped,
					   msecs_to_jiffies(2));
	} while (!data->intr_pin && !data->touch_stopped);

	return IRQ_HANDLED;
}