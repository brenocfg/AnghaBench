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
typedef  scalar_t__ u8 ;
struct ingenic_pinctrl {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 unsigned int PINS_PER_GPIO_CHIP ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static inline bool ingenic_get_pin_config(struct ingenic_pinctrl *jzpc,
		unsigned int pin, u8 reg)
{
	unsigned int idx = pin % PINS_PER_GPIO_CHIP;
	unsigned int offt = pin / PINS_PER_GPIO_CHIP;
	unsigned int val;

	regmap_read(jzpc->map, offt * 0x100 + reg, &val);

	return val & BIT(idx);
}