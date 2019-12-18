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
struct platform_device {struct device dev; } ;
struct gpio_chip {char* label; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  ngpio; scalar_t__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LOONGSON_N_GPIO ; 
 struct gpio_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (struct gpio_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loongson_gpio_direction_input ; 
 int /*<<< orphan*/  loongson_gpio_direction_output ; 
 int /*<<< orphan*/  loongson_gpio_get_value ; 
 int /*<<< orphan*/  loongson_gpio_set_value ; 

__attribute__((used)) static int loongson_gpio_probe(struct platform_device *pdev)
{
	struct gpio_chip *gc;
	struct device *dev = &pdev->dev;

	gc = devm_kzalloc(dev, sizeof(*gc), GFP_KERNEL);
	if (!gc)
		return -ENOMEM;

	gc->label = "loongson-gpio-chip";
	gc->base = 0;
	gc->ngpio = LOONGSON_N_GPIO;
	gc->get = loongson_gpio_get_value;
	gc->set = loongson_gpio_set_value;
	gc->direction_input = loongson_gpio_direction_input;
	gc->direction_output = loongson_gpio_direction_output;

	return gpiochip_add_data(gc, NULL);
}