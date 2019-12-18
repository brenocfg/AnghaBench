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
struct adv7511 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7511_INT1_DDC_ERROR ; 
 int /*<<< orphan*/  ADV7511_POWER_POWER_DOWN ; 
 int /*<<< orphan*/  ADV7511_REG_INT_ENABLE (int) ; 
 int /*<<< orphan*/  ADV7511_REG_POWER ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __adv7511_power_off(struct adv7511 *adv7511)
{
	/* TODO: setup additional power down modes */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_POWER,
			   ADV7511_POWER_POWER_DOWN,
			   ADV7511_POWER_POWER_DOWN);
	regmap_update_bits(adv7511->regmap,
			   ADV7511_REG_INT_ENABLE(1),
			   ADV7511_INT1_DDC_ERROR, 0);
	regcache_mark_dirty(adv7511->regmap);
}