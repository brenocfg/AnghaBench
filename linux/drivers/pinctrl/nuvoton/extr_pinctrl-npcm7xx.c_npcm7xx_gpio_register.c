#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct npcm7xx_pinctrl {int bank_num; TYPE_6__* gpio_bank; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  ngpio; int /*<<< orphan*/  base; } ;
struct TYPE_8__ {TYPE_1__ gc; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_chip; int /*<<< orphan*/  pinctrl_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ ,TYPE_1__*,TYPE_6__*) ; 
 int gpiochip_add_pin_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpiochip_irqchip_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  npcmgpio_irq_handler ; 

__attribute__((used)) static int npcm7xx_gpio_register(struct npcm7xx_pinctrl *pctrl)
{
	int ret, id;

	for (id = 0 ; id < pctrl->bank_num ; id++) {
		ret = devm_gpiochip_add_data(pctrl->dev,
					     &pctrl->gpio_bank[id].gc,
					     &pctrl->gpio_bank[id]);
		if (ret) {
			dev_err(pctrl->dev, "Failed to add GPIO chip %u\n", id);
			goto err_register;
		}

		ret = gpiochip_add_pin_range(&pctrl->gpio_bank[id].gc,
					     dev_name(pctrl->dev),
					     pctrl->gpio_bank[id].pinctrl_id,
					     pctrl->gpio_bank[id].gc.base,
					     pctrl->gpio_bank[id].gc.ngpio);
		if (ret < 0) {
			dev_err(pctrl->dev, "Failed to add GPIO bank %u\n", id);
			gpiochip_remove(&pctrl->gpio_bank[id].gc);
			goto err_register;
		}

		ret = gpiochip_irqchip_add(&pctrl->gpio_bank[id].gc,
					   &pctrl->gpio_bank[id].irq_chip,
					   0, handle_level_irq,
					   IRQ_TYPE_NONE);
		if (ret < 0) {
			dev_err(pctrl->dev,
				"Failed to add IRQ chip %u\n", id);
			gpiochip_remove(&pctrl->gpio_bank[id].gc);
			goto err_register;
		}

		gpiochip_set_chained_irqchip(&pctrl->gpio_bank[id].gc,
					     &pctrl->gpio_bank[id].irq_chip,
					     pctrl->gpio_bank[id].irq,
					     npcmgpio_irq_handler);
	}

	return 0;

err_register:
	for (; id > 0; id--)
		gpiochip_remove(&pctrl->gpio_bank[id - 1].gc);

	return ret;
}