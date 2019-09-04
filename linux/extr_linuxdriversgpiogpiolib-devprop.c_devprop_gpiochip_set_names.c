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
struct gpio_device {int ngpio; TYPE_1__* descs; int /*<<< orphan*/  dev; } ;
struct gpio_chip {struct gpio_device* gpiodev; } ;
struct fwnode_handle {int dummy; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int fwnode_property_read_string_array (struct fwnode_handle const*,char*,char const**,int) ; 
 char** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char const**) ; 

void devprop_gpiochip_set_names(struct gpio_chip *chip,
				const struct fwnode_handle *fwnode)
{
	struct gpio_device *gdev = chip->gpiodev;
	const char **names;
	int ret, i;

	ret = fwnode_property_read_string_array(fwnode, "gpio-line-names",
						NULL, 0);
	if (ret < 0)
		return;

	if (ret != gdev->ngpio) {
		dev_warn(&gdev->dev,
			 "names %d do not match number of GPIOs %d\n", ret,
			 gdev->ngpio);
		return;
	}

	names = kcalloc(gdev->ngpio, sizeof(*names), GFP_KERNEL);
	if (!names)
		return;

	ret = fwnode_property_read_string_array(fwnode, "gpio-line-names",
						names, gdev->ngpio);
	if (ret < 0) {
		dev_warn(&gdev->dev, "failed to read GPIO line names\n");
		kfree(names);
		return;
	}

	for (i = 0; i < gdev->ngpio; i++)
		gdev->descs[i].name = names[i];

	kfree(names);
}