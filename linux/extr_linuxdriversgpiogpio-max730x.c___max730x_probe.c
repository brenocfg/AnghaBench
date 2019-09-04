#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct max7301_platform_data {int base; int /*<<< orphan*/  input_pullup_active; } ;
struct TYPE_5__ {int base; int (* direction_input ) (TYPE_2__*,int) ;int can_sleep; int /*<<< orphan*/  owner; struct device* parent; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  label; } ;
struct max7301 {int* port_config; int /*<<< orphan*/  lock; TYPE_2__ chip; int /*<<< orphan*/  input_pullup_active; int /*<<< orphan*/  (* write ) (struct device*,int,int) ;struct device* dev; } ;
struct device {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIN_NUMBER ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct max7301_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct max7301*) ; 
 int gpiochip_add_data (TYPE_2__*,struct max7301*) ; 
 int max7301_direction_input (TYPE_2__*,int) ; 
 int /*<<< orphan*/  max7301_direction_output ; 
 int /*<<< orphan*/  max7301_get ; 
 int /*<<< orphan*/  max7301_set ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct device*,int,int) ; 

int __max730x_probe(struct max7301 *ts)
{
	struct device *dev = ts->dev;
	struct max7301_platform_data *pdata;
	int i, ret;

	pdata = dev_get_platdata(dev);

	mutex_init(&ts->lock);
	dev_set_drvdata(dev, ts);

	/* Power up the chip and disable IRQ output */
	ts->write(dev, 0x04, 0x01);

	if (pdata) {
		ts->input_pullup_active = pdata->input_pullup_active;
		ts->chip.base = pdata->base;
	} else {
		ts->chip.base = -1;
	}
	ts->chip.label = dev->driver->name;

	ts->chip.direction_input = max7301_direction_input;
	ts->chip.get = max7301_get;
	ts->chip.direction_output = max7301_direction_output;
	ts->chip.set = max7301_set;

	ts->chip.ngpio = PIN_NUMBER;
	ts->chip.can_sleep = true;
	ts->chip.parent = dev;
	ts->chip.owner = THIS_MODULE;

	ret = gpiochip_add_data(&ts->chip, ts);
	if (ret)
		goto exit_destroy;

	/*
	 * initialize pullups according to platform data and cache the
	 * register values for later use.
	 */
	for (i = 1; i < 8; i++) {
		int j;
		/*
		 * initialize port_config with "0xAA", which means
		 * input with internal pullup disabled. This is needed
		 * to avoid writing zeros (in the inner for loop),
		 * which is not allowed according to the datasheet.
		 */
		ts->port_config[i] = 0xAA;
		for (j = 0; j < 4; j++) {
			int offset = (i - 1) * 4 + j;
			ret = max7301_direction_input(&ts->chip, offset);
			if (ret)
				goto exit_destroy;
		}
	}

	return ret;

exit_destroy:
	mutex_destroy(&ts->lock);
	return ret;
}