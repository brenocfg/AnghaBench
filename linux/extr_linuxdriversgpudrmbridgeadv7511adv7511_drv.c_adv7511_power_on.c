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
struct adv7511 {scalar_t__ type; int powered; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ADV7533 ; 
 int /*<<< orphan*/  __adv7511_power_on (struct adv7511*) ; 
 int /*<<< orphan*/  adv7533_dsi_power_on (struct adv7511*) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adv7511_power_on(struct adv7511 *adv7511)
{
	__adv7511_power_on(adv7511);

	/*
	 * Most of the registers are reset during power down or when HPD is low.
	 */
	regcache_sync(adv7511->regmap);

	if (adv7511->type == ADV7533)
		adv7533_dsi_power_on(adv7511);
	adv7511->powered = true;
}