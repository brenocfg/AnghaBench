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
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,char const*) ; 
 int gpio_direction_output (int,int) ; 
 int gpio_export (int,int) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int gpio_request (int,char const*) ; 

__attribute__((used)) static int vip_gpio_reserve(struct device *dev, int pin, int dir,
			    const char *name)
{
	int ret = -ENODEV;

	if (!gpio_is_valid(pin))
		return ret;

	ret = gpio_request(pin, name);
	if (ret) {
		dev_err(dev, "Failed to allocate pin %d (%s)\n", pin, name);
		return ret;
	}

	ret = gpio_direction_output(pin, dir);
	if (ret) {
		dev_err(dev, "Failed to set direction for pin %d (%s)\n",
			pin, name);
		gpio_free(pin);
		return ret;
	}

	ret = gpio_export(pin, false);
	if (ret) {
		dev_err(dev, "Failed to export pin %d (%s)\n", pin, name);
		gpio_free(pin);
		return ret;
	}

	return 0;
}