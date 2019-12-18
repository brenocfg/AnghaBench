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
struct hdmi_platform_config {struct hdmi_gpio_data* gpios; } ;
struct hdmi_gpio_data {int value; scalar_t__ gpiod; scalar_t__ output; } ;
struct hdmi {struct hdmi_platform_config* config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int HDMI_MAX_NUM_GPIO ; 
 int /*<<< orphan*/  gpiod_direction_input (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_direction_output (scalar_t__,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 

__attribute__((used)) static int gpio_config(struct hdmi *hdmi, bool on)
{
	const struct hdmi_platform_config *config = hdmi->config;
	int i;

	if (on) {
		for (i = 0; i < HDMI_MAX_NUM_GPIO; i++) {
			struct hdmi_gpio_data gpio = config->gpios[i];

			if (gpio.gpiod) {
				if (gpio.output) {
					gpiod_direction_output(gpio.gpiod,
							       gpio.value);
				} else {
					gpiod_direction_input(gpio.gpiod);
					gpiod_set_value_cansleep(gpio.gpiod,
								 gpio.value);
				}
			}
		}

		DBG("gpio on");
	} else {
		for (i = 0; i < HDMI_MAX_NUM_GPIO; i++) {
			struct hdmi_gpio_data gpio = config->gpios[i];

			if (!gpio.gpiod)
				continue;

			if (gpio.output) {
				int value = gpio.value ? 0 : 1;

				gpiod_set_value_cansleep(gpio.gpiod, value);
			}
		};

		DBG("gpio off");
	}

	return 0;
}