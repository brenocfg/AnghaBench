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
struct nokia_modem_device {int gpio_amount; TYPE_1__* gpios; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct nokia_modem_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  devm_gpiod_get_index (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int gpiod_export (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpiod_export_link (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_gpio_count (struct device_node*) ; 
 int of_property_count_strings (struct device_node*,char*) ; 
 int of_property_read_string_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nokia_modem_gpio_probe(struct device *dev)
{
	struct device_node *np = dev->of_node;
	struct nokia_modem_device *modem = dev_get_drvdata(dev);
	int gpio_count, gpio_name_count, i, err;

	gpio_count = of_gpio_count(np);

	if (gpio_count < 0) {
		dev_err(dev, "missing gpios: %d\n", gpio_count);
		return gpio_count;
	}

	gpio_name_count = of_property_count_strings(np, "gpio-names");

	if (gpio_count != gpio_name_count) {
		dev_err(dev, "number of gpios does not equal number of gpio names\n");
		return -EINVAL;
	}

	modem->gpios = devm_kcalloc(dev, gpio_count, sizeof(*modem->gpios),
				    GFP_KERNEL);
	if (!modem->gpios)
		return -ENOMEM;

	modem->gpio_amount = gpio_count;

	for (i = 0; i < gpio_count; i++) {
		modem->gpios[i].gpio = devm_gpiod_get_index(dev, NULL, i,
							    GPIOD_OUT_LOW);
		if (IS_ERR(modem->gpios[i].gpio)) {
			dev_err(dev, "Could not get gpio %d\n", i);
			return PTR_ERR(modem->gpios[i].gpio);
		}

		err = of_property_read_string_index(np, "gpio-names", i,
						&(modem->gpios[i].name));
		if (err) {
			dev_err(dev, "Could not get gpio name %d\n", i);
			return err;
		}

		err = gpiod_export(modem->gpios[i].gpio, 0);
		if (err)
			return err;

		err = gpiod_export_link(dev, modem->gpios[i].name,
							modem->gpios[i].gpio);
		if (err)
			return err;
	}

	return 0;
}