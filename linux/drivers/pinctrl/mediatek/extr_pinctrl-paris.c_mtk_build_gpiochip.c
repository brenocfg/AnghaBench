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
struct gpio_chip {int base; int of_gpio_n_cells; struct device_node* of_node; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  set_config; int /*<<< orphan*/  to_irq; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  parent; int /*<<< orphan*/  label; } ;
struct mtk_pinctrl {TYPE_1__* soc; int /*<<< orphan*/  dev; struct gpio_chip chip; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  npins; } ;

/* Variables and functions */
 int /*<<< orphan*/  PINCTRL_PINCTRL_DEV ; 
 int gpiochip_add_data (struct gpio_chip*,struct mtk_pinctrl*) ; 
 int /*<<< orphan*/  gpiochip_generic_free ; 
 int /*<<< orphan*/  gpiochip_generic_request ; 
 int /*<<< orphan*/  mtk_gpio_direction_input ; 
 int /*<<< orphan*/  mtk_gpio_direction_output ; 
 int /*<<< orphan*/  mtk_gpio_get ; 
 int /*<<< orphan*/  mtk_gpio_get_direction ; 
 int /*<<< orphan*/  mtk_gpio_set ; 
 int /*<<< orphan*/  mtk_gpio_set_config ; 
 int /*<<< orphan*/  mtk_gpio_to_irq ; 

__attribute__((used)) static int mtk_build_gpiochip(struct mtk_pinctrl *hw, struct device_node *np)
{
	struct gpio_chip *chip = &hw->chip;
	int ret;

	chip->label		= PINCTRL_PINCTRL_DEV;
	chip->parent		= hw->dev;
	chip->request		= gpiochip_generic_request;
	chip->free		= gpiochip_generic_free;
	chip->get_direction	= mtk_gpio_get_direction;
	chip->direction_input	= mtk_gpio_direction_input;
	chip->direction_output	= mtk_gpio_direction_output;
	chip->get		= mtk_gpio_get;
	chip->set		= mtk_gpio_set;
	chip->to_irq		= mtk_gpio_to_irq,
	chip->set_config	= mtk_gpio_set_config,
	chip->base		= -1;
	chip->ngpio		= hw->soc->npins;
	chip->of_node		= np;
	chip->of_gpio_n_cells	= 2;

	ret = gpiochip_add_data(chip, hw);
	if (ret < 0)
		return ret;

	return 0;
}