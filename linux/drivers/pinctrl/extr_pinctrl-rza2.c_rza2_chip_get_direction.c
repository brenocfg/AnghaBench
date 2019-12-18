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
typedef  int u8 ;
typedef  int u16 ;
struct rza2_pinctrl_priv {scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ RZA2_PDR (int) ; 
 int RZA2_PDR_INPUT ; 
 int RZA2_PDR_MASK ; 
 int RZA2_PDR_OUTPUT ; 
 int RZA2_PIN_ID_TO_PIN (unsigned int) ; 
 int RZA2_PIN_ID_TO_PORT (unsigned int) ; 
 struct rza2_pinctrl_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  rza2_pin_to_gpio (scalar_t__,unsigned int,int) ; 

__attribute__((used)) static int rza2_chip_get_direction(struct gpio_chip *chip, unsigned int offset)
{
	struct rza2_pinctrl_priv *priv = gpiochip_get_data(chip);
	u8 port = RZA2_PIN_ID_TO_PORT(offset);
	u8 pin = RZA2_PIN_ID_TO_PIN(offset);
	u16 reg16;

	reg16 = readw(priv->base + RZA2_PDR(port));
	reg16 = (reg16 >> (pin * 2)) & RZA2_PDR_MASK;

	if (reg16 == RZA2_PDR_OUTPUT)
		return 0;

	if (reg16 == RZA2_PDR_INPUT)
		return 1;

	/*
	 * This GPIO controller has a default Hi-Z state that is not input or
	 * output, so force the pin to input now.
	 */
	rza2_pin_to_gpio(priv->base, offset, 1);

	return 1;
}