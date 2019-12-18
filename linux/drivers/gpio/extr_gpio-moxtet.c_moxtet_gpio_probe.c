#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int base; int can_sleep; int /*<<< orphan*/  owner; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  label; struct device* parent; } ;
struct moxtet_gpio_chip {TYPE_2__ gpio_chip; int /*<<< orphan*/ * desc; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MOXTET_GPIO_NGPIOS ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/ * descs ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct device_node*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct moxtet_gpio_chip*) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_2__*,struct moxtet_gpio_chip*) ; 
 struct moxtet_gpio_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moxtet_gpio_direction_input ; 
 int /*<<< orphan*/  moxtet_gpio_direction_output ; 
 int /*<<< orphan*/  moxtet_gpio_get_direction ; 
 int /*<<< orphan*/  moxtet_gpio_get_value ; 
 int /*<<< orphan*/  moxtet_gpio_set_value ; 
 TYPE_1__* to_moxtet_device (struct device*) ; 

__attribute__((used)) static int moxtet_gpio_probe(struct device *dev)
{
	struct moxtet_gpio_chip *chip;
	struct device_node *nc = dev->of_node;
	int id;

	id = to_moxtet_device(dev)->id;

	if (id >= ARRAY_SIZE(descs)) {
		dev_err(dev, "%pOF Moxtet device id 0x%x is not supported by gpio-moxtet driver\n",
			nc, id);
		return -ENOTSUPP;
	}

	chip = devm_kzalloc(dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->dev = dev;
	chip->gpio_chip.parent = dev;
	chip->desc = &descs[id];

	dev_set_drvdata(dev, chip);

	chip->gpio_chip.label = dev_name(dev);
	chip->gpio_chip.get_direction = moxtet_gpio_get_direction;
	chip->gpio_chip.direction_input = moxtet_gpio_direction_input;
	chip->gpio_chip.direction_output = moxtet_gpio_direction_output;
	chip->gpio_chip.get = moxtet_gpio_get_value;
	chip->gpio_chip.set = moxtet_gpio_set_value;
	chip->gpio_chip.base = -1;

	chip->gpio_chip.ngpio = MOXTET_GPIO_NGPIOS;

	chip->gpio_chip.can_sleep = true;
	chip->gpio_chip.owner = THIS_MODULE;

	return devm_gpiochip_add_data(dev, &chip->gpio_chip, chip);
}