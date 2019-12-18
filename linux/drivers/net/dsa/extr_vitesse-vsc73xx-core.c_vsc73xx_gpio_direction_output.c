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
typedef  int u32 ;
struct vsc73xx {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_SYSTEM ; 
 int /*<<< orphan*/  VSC73XX_GPIO ; 
 struct vsc73xx* gpiochip_get_data (struct gpio_chip*) ; 
 int vsc73xx_update_bits (struct vsc73xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int vsc73xx_gpio_direction_output(struct gpio_chip *chip,
					 unsigned int offset, int val)
{
	struct vsc73xx *vsc = gpiochip_get_data(chip);
	u32 tmp = val ? BIT(offset) : 0;

	return vsc73xx_update_bits(vsc, VSC73XX_BLOCK_SYSTEM, 0,
				   VSC73XX_GPIO, BIT(offset + 4) | BIT(offset),
				   BIT(offset + 4) | tmp);
}