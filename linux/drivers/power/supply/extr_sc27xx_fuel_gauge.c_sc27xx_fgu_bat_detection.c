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
struct sc27xx_fgu_data {int bat_present; int /*<<< orphan*/  battery; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  gpiod; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sc27xx_fgu_bat_detection(int irq, void *dev_id)
{
	struct sc27xx_fgu_data *data = dev_id;
	int state;

	mutex_lock(&data->lock);

	state = gpiod_get_value_cansleep(data->gpiod);
	if (state < 0) {
		dev_err(data->dev, "failed to get gpio state\n");
		mutex_unlock(&data->lock);
		return IRQ_RETVAL(state);
	}

	data->bat_present = !!state;

	mutex_unlock(&data->lock);

	power_supply_changed(data->battery);
	return IRQ_HANDLED;
}