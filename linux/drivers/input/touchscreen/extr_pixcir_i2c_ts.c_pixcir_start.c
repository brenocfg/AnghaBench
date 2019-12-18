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
struct pixcir_i2c_ts_data {int running; scalar_t__ gpio_enable; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIXCIR_INT_LEVEL_TOUCH ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pixcir_int_enable (struct pixcir_i2c_ts_data*,int) ; 
 int pixcir_set_int_mode (struct pixcir_i2c_ts_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pixcir_start(struct pixcir_i2c_ts_data *ts)
{
	struct device *dev = &ts->client->dev;
	int error;

	if (ts->gpio_enable) {
		gpiod_set_value_cansleep(ts->gpio_enable, 1);
		msleep(100);
	}

	/* LEVEL_TOUCH interrupt with active low polarity */
	error = pixcir_set_int_mode(ts, PIXCIR_INT_LEVEL_TOUCH, 0);
	if (error) {
		dev_err(dev, "Failed to set interrupt mode: %d\n", error);
		return error;
	}

	ts->running = true;
	mb();	/* Update status before IRQ can fire */

	/* enable interrupt generation */
	error = pixcir_int_enable(ts, true);
	if (error) {
		dev_err(dev, "Failed to enable interrupt generation: %d\n",
			error);
		return error;
	}

	return 0;
}