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
struct hdmi_platform_config {struct hdmi_gpio_data* gpios; } ;
struct hdmi_gpio_data {int num; int value; scalar_t__ output; int /*<<< orphan*/  label; } ;
struct hdmi {struct hdmi_platform_config* config; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int HDMI_MAX_NUM_GPIO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int gpio_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int,int) ; 

__attribute__((used)) static int gpio_config(struct hdmi *hdmi, bool on)
{
	struct device *dev = &hdmi->pdev->dev;
	const struct hdmi_platform_config *config = hdmi->config;
	int ret, i;

	if (on) {
		for (i = 0; i < HDMI_MAX_NUM_GPIO; i++) {
			struct hdmi_gpio_data gpio = config->gpios[i];

			if (gpio.num != -1) {
				ret = gpio_request(gpio.num, gpio.label);
				if (ret) {
					dev_err(dev,
						"'%s'(%d) gpio_request failed: %d\n",
						gpio.label, gpio.num, ret);
					goto err;
				}

				if (gpio.output) {
					gpio_direction_output(gpio.num,
							      gpio.value);
				} else {
					gpio_direction_input(gpio.num);
					gpio_set_value_cansleep(gpio.num,
								gpio.value);
				}
			}
		}

		DBG("gpio on");
	} else {
		for (i = 0; i < HDMI_MAX_NUM_GPIO; i++) {
			struct hdmi_gpio_data gpio = config->gpios[i];

			if (gpio.num == -1)
				continue;

			if (gpio.output) {
				int value = gpio.value ? 0 : 1;

				gpio_set_value_cansleep(gpio.num, value);
			}

			gpio_free(gpio.num);
		};

		DBG("gpio off");
	}

	return 0;
err:
	while (i--) {
		if (config->gpios[i].num != -1)
			gpio_free(config->gpios[i].num);
	}

	return ret;
}