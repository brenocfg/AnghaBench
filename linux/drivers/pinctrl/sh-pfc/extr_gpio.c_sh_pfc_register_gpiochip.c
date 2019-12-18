#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sh_pfc_window {scalar_t__ phys; scalar_t__ size; } ;
struct sh_pfc_pin_range {scalar_t__ start; scalar_t__ end; } ;
struct sh_pfc_chip {int /*<<< orphan*/  gpio_chip; } ;
struct sh_pfc {unsigned int num_windows; scalar_t__ num_irqs; unsigned int nr_ranges; scalar_t__ nr_gpio_pins; TYPE_2__* info; TYPE_3__* dev; struct sh_pfc_pin_range* ranges; struct sh_pfc_chip* gpio; struct sh_pfc_window* windows; } ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_7__ {scalar_t__ of_node; } ;
struct TYPE_6__ {scalar_t__ gpio_irq_size; scalar_t__ nr_func_gpios; TYPE_1__* data_regs; } ;
struct TYPE_5__ {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int EINVAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct sh_pfc_chip*) ; 
 int PTR_ERR (struct sh_pfc_chip*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  gpio_function_setup ; 
 int /*<<< orphan*/  gpio_pin_setup ; 
 int gpiochip_add_pin_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 struct sh_pfc_chip* sh_pfc_add_gpiochip (struct sh_pfc*,int /*<<< orphan*/ ,struct sh_pfc_window*) ; 

int sh_pfc_register_gpiochip(struct sh_pfc *pfc)
{
	struct sh_pfc_chip *chip;
	phys_addr_t address;
	unsigned int i;

	if (pfc->info->data_regs == NULL)
		return 0;

	/* Find the memory window that contain the GPIO registers. Boards that
	 * register a separate GPIO device will not supply a memory resource
	 * that covers the data registers. In that case don't try to handle
	 * GPIOs.
	 */
	address = pfc->info->data_regs[0].reg;
	for (i = 0; i < pfc->num_windows; ++i) {
		struct sh_pfc_window *window = &pfc->windows[i];

		if (address >= window->phys &&
		    address < window->phys + window->size)
			break;
	}

	if (i == pfc->num_windows)
		return 0;

	/* If we have IRQ resources make sure their number is correct. */
	if (pfc->num_irqs != pfc->info->gpio_irq_size) {
		dev_err(pfc->dev, "invalid number of IRQ resources\n");
		return -EINVAL;
	}

	/* Register the real GPIOs chip. */
	chip = sh_pfc_add_gpiochip(pfc, gpio_pin_setup, &pfc->windows[i]);
	if (IS_ERR(chip))
		return PTR_ERR(chip);

	pfc->gpio = chip;

	if (IS_ENABLED(CONFIG_OF) && pfc->dev->of_node)
		return 0;

#ifdef CONFIG_PINCTRL_SH_FUNC_GPIO
	/*
	 * Register the GPIO to pin mappings. As pins with GPIO ports
	 * must come first in the ranges, skip the pins without GPIO
	 * ports by stopping at the first range that contains such a
	 * pin.
	 */
	for (i = 0; i < pfc->nr_ranges; ++i) {
		const struct sh_pfc_pin_range *range = &pfc->ranges[i];
		int ret;

		if (range->start >= pfc->nr_gpio_pins)
			break;

		ret = gpiochip_add_pin_range(&chip->gpio_chip,
			dev_name(pfc->dev), range->start, range->start,
			range->end - range->start + 1);
		if (ret < 0)
			return ret;
	}

	/* Register the function GPIOs chip. */
	if (pfc->info->nr_func_gpios == 0)
		return 0;

	chip = sh_pfc_add_gpiochip(pfc, gpio_function_setup, NULL);
	if (IS_ERR(chip))
		return PTR_ERR(chip);
#endif /* CONFIG_PINCTRL_SH_FUNC_GPIO */

	return 0;
}