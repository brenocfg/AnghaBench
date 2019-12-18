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
struct ingenic_pinctrl {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 unsigned int PINS_PER_GPIO_CHIP ; 
 int /*<<< orphan*/  X1000_GPIO_PZ_GID2LD ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void ingenic_shadow_config_pin_load(struct ingenic_pinctrl *jzpc,
		unsigned int pin)
{
	regmap_write(jzpc->map, X1000_GPIO_PZ_GID2LD, pin / PINS_PER_GPIO_CHIP);
}