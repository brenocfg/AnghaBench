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
typedef  scalar_t__ u32 ;
struct sc2731_charger_info {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ SC2731_CHG_CFG0 ; 
 scalar_t__ SC2731_CHG_CFG1 ; 
 scalar_t__ SC2731_CURRENT_LIMIT_2000 ; 
 scalar_t__ SC2731_CURRENT_PRECHG ; 
 scalar_t__ SC2731_CURRENT_STEP ; 
 int /*<<< orphan*/  SC2731_CUR_MASK ; 
 int /*<<< orphan*/  SC2731_PRECHG_RNG_MASK ; 
 int SC2731_PRECHG_RNG_SHIFT ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sc2731_charger_set_current(struct sc2731_charger_info *info, u32 cur)
{
	u32 val;
	int ret;

	if (cur > SC2731_CURRENT_LIMIT_2000)
		cur = SC2731_CURRENT_LIMIT_2000;
	else if (cur < SC2731_CURRENT_PRECHG)
		cur = SC2731_CURRENT_PRECHG;

	/* Calculate the step value, each step is 50 mA */
	val = (cur - SC2731_CURRENT_PRECHG) / SC2731_CURRENT_STEP;

	/* Set pre-charge current as 450 mA */
	ret = regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG0,
				 SC2731_PRECHG_RNG_MASK,
				 0x3 << SC2731_PRECHG_RNG_SHIFT);
	if (ret)
		return ret;

	return regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG1,
				  SC2731_CUR_MASK, val);
}