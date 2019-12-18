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
struct ep93xx_gpio {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int* gpio_int_enabled ; 
 int /*<<< orphan*/ * gpio_int_type1 ; 
 int /*<<< orphan*/ * gpio_int_type2 ; 
 int* gpio_int_unmasked ; 
 scalar_t__* int_en_register_offset ; 
 scalar_t__* int_type1_register_offset ; 
 scalar_t__* int_type2_register_offset ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writeb_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ep93xx_gpio_update_int_params(struct ep93xx_gpio *epg, unsigned port)
{
	BUG_ON(port > 2);

	writeb_relaxed(0, epg->base + int_en_register_offset[port]);

	writeb_relaxed(gpio_int_type2[port],
		       epg->base + int_type2_register_offset[port]);

	writeb_relaxed(gpio_int_type1[port],
		       epg->base + int_type1_register_offset[port]);

	writeb(gpio_int_unmasked[port] & gpio_int_enabled[port],
	       epg->base + int_en_register_offset[port]);
}