#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int base; } ;
struct ingenic_gpio_chip {TYPE_2__ gc; TYPE_1__* jzpc; } ;
struct TYPE_3__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int PINS_PER_GPIO_CHIP ; 
 int /*<<< orphan*/  X1000_GPIO_PZ_GID2LD ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ingenic_gpio_shadow_set_bit_load(struct ingenic_gpio_chip *jzgc)
{
	regmap_write(jzgc->jzpc->map, X1000_GPIO_PZ_GID2LD,
			jzgc->gc.base / PINS_PER_GPIO_CHIP);
}