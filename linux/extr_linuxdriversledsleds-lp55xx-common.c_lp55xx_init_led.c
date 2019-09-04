#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lp55xx_platform_data {scalar_t__ label; TYPE_1__* led_config; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  groups; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  default_trigger; } ;
struct lp55xx_led {scalar_t__ led_current; int chan_nr; TYPE_3__ cdev; int /*<<< orphan*/  max_current; } ;
struct lp55xx_device_config {int max_channel; } ;
struct lp55xx_chip {TYPE_2__* cl; struct lp55xx_device_config* cfg; struct lp55xx_platform_data* pdata; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_5__ {char* name; struct device dev; } ;
struct TYPE_4__ {scalar_t__ led_current; int chan_nr; char* name; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  max_current; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int led_classdev_register (struct device*,TYPE_3__*) ; 
 int /*<<< orphan*/  lp55xx_led_groups ; 
 int /*<<< orphan*/  lp55xx_set_brightness ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static int lp55xx_init_led(struct lp55xx_led *led,
			struct lp55xx_chip *chip, int chan)
{
	struct lp55xx_platform_data *pdata = chip->pdata;
	struct lp55xx_device_config *cfg = chip->cfg;
	struct device *dev = &chip->cl->dev;
	char name[32];
	int ret;
	int max_channel = cfg->max_channel;

	if (chan >= max_channel) {
		dev_err(dev, "invalid channel: %d / %d\n", chan, max_channel);
		return -EINVAL;
	}

	if (pdata->led_config[chan].led_current == 0)
		return 0;

	led->led_current = pdata->led_config[chan].led_current;
	led->max_current = pdata->led_config[chan].max_current;
	led->chan_nr = pdata->led_config[chan].chan_nr;
	led->cdev.default_trigger = pdata->led_config[chan].default_trigger;

	if (led->chan_nr >= max_channel) {
		dev_err(dev, "Use channel numbers between 0 and %d\n",
			max_channel - 1);
		return -EINVAL;
	}

	led->cdev.brightness_set_blocking = lp55xx_set_brightness;
	led->cdev.groups = lp55xx_led_groups;

	if (pdata->led_config[chan].name) {
		led->cdev.name = pdata->led_config[chan].name;
	} else {
		snprintf(name, sizeof(name), "%s:channel%d",
			pdata->label ? : chip->cl->name, chan);
		led->cdev.name = name;
	}

	ret = led_classdev_register(dev, &led->cdev);
	if (ret) {
		dev_err(dev, "led register err: %d\n", ret);
		return ret;
	}

	return 0;
}