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
 scalar_t__ SC2731_CHG_CFG5 ; 
 scalar_t__ SC2731_CURRENT_LIMIT_100 ; 
 scalar_t__ SC2731_CURRENT_LIMIT_500 ; 
 scalar_t__ SC2731_CURRENT_LIMIT_900 ; 
 int /*<<< orphan*/  SC2731_CUR_LIMIT_MASK ; 
 scalar_t__ SC2731_CUR_LIMIT_SHIFT ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sc2731_charger_set_current_limit(struct sc2731_charger_info *info,
					    u32 limit)
{
	u32 val;

	if (limit <= SC2731_CURRENT_LIMIT_100)
		val = 0;
	else if (limit <= SC2731_CURRENT_LIMIT_500)
		val = 3;
	else if (limit <= SC2731_CURRENT_LIMIT_900)
		val = 2;
	else
		val = 1;

	return regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG5,
				  SC2731_CUR_LIMIT_MASK,
				  val << SC2731_CUR_LIMIT_SHIFT);
}