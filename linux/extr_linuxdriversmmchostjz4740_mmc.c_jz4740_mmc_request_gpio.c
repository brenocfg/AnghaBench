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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,int) ; 
 int /*<<< orphan*/  gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int gpio_request (int,char const*) ; 

__attribute__((used)) static int jz4740_mmc_request_gpio(struct device *dev, int gpio,
	const char *name, bool output, int value)
{
	int ret;

	if (!gpio_is_valid(gpio))
		return 0;

	ret = gpio_request(gpio, name);
	if (ret) {
		dev_err(dev, "Failed to request %s gpio: %d\n", name, ret);
		return ret;
	}

	if (output)
		gpio_direction_output(gpio, value);
	else
		gpio_direction_input(gpio);

	return 0;
}