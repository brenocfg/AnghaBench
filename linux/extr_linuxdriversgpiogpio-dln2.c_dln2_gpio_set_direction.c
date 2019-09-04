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
struct gpio_chip {int dummy; } ;
struct dln2_gpio_pin_val {unsigned int value; int /*<<< orphan*/  pin; } ;
struct dln2_gpio {int /*<<< orphan*/  output_enabled; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 unsigned int DLN2_GPIO_DIRECTION_OUT ; 
 int /*<<< orphan*/  DLN2_GPIO_PIN_SET_DIRECTION ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int dln2_transfer_tx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dln2_gpio_pin_val*,int) ; 
 struct dln2_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dln2_gpio_set_direction(struct gpio_chip *chip, unsigned offset,
				   unsigned dir)
{
	struct dln2_gpio *dln2 = gpiochip_get_data(chip);
	struct dln2_gpio_pin_val req = {
		.pin = cpu_to_le16(offset),
		.value = dir,
	};
	int ret;

	ret = dln2_transfer_tx(dln2->pdev, DLN2_GPIO_PIN_SET_DIRECTION,
			       &req, sizeof(req));
	if (ret < 0)
		return ret;

	if (dir == DLN2_GPIO_DIRECTION_OUT)
		set_bit(offset, dln2->output_enabled);
	else
		clear_bit(offset, dln2->output_enabled);

	return ret;
}