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
struct sc2731_charger_info {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC2731_CC_EN ; 
 int /*<<< orphan*/  SC2731_CHARGER_PD ; 
 scalar_t__ SC2731_CHG_CFG0 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc2731_charger_stop_charge(struct sc2731_charger_info *info)
{
	regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG0,
			   SC2731_CC_EN, 0);

	regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG0,
			   SC2731_CHARGER_PD, SC2731_CHARGER_PD);
}