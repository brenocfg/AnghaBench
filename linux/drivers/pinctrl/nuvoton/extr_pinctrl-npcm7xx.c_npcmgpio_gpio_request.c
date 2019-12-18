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
struct npcm7xx_gpio {int (* request ) (struct gpio_chip*,unsigned int) ;} ;
struct gpio_chip {scalar_t__ base; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct npcm7xx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int pinctrl_gpio_request (scalar_t__) ; 
 int stub1 (struct gpio_chip*,unsigned int) ; 

__attribute__((used)) static int npcmgpio_gpio_request(struct gpio_chip *chip, unsigned int offset)
{
	struct npcm7xx_gpio *bank = gpiochip_get_data(chip);
	int ret;

	dev_dbg(chip->parent, "gpio_request: offset%d\n", offset);
	ret = pinctrl_gpio_request(offset + chip->base);
	if (ret)
		return ret;

	return bank->request(chip, offset);
}