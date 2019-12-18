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
typedef  int /*<<< orphan*/  u8 ;
struct rza2_pinctrl_priv {scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ RZA2_PIDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RZA2_PIN_ID_TO_PIN (unsigned int) ; 
 int /*<<< orphan*/  RZA2_PIN_ID_TO_PORT (unsigned int) ; 
 struct rza2_pinctrl_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static int rza2_chip_get(struct gpio_chip *chip, unsigned int offset)
{
	struct rza2_pinctrl_priv *priv = gpiochip_get_data(chip);
	u8 port = RZA2_PIN_ID_TO_PORT(offset);
	u8 pin = RZA2_PIN_ID_TO_PIN(offset);

	return !!(readb(priv->base + RZA2_PIDR(port)) & BIT(pin));
}