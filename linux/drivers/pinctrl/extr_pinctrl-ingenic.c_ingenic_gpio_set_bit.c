#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct ingenic_gpio_chip {scalar_t__ reg_base; TYPE_1__* jzpc; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 scalar_t__ REG_CLEAR (scalar_t__) ; 
 scalar_t__ REG_SET (scalar_t__) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ingenic_gpio_set_bit(struct ingenic_gpio_chip *jzgc,
		u8 reg, u8 offset, bool set)
{
	if (set)
		reg = REG_SET(reg);
	else
		reg = REG_CLEAR(reg);

	regmap_write(jzgc->jzpc->map, jzgc->reg_base + reg, BIT(offset));
}