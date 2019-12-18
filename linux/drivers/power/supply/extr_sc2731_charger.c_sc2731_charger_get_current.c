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
typedef  int u32 ;
struct sc2731_charger_info {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ SC2731_CHG_CFG1 ; 
 int SC2731_CURRENT_PRECHG ; 
 int SC2731_CURRENT_STEP ; 
 int SC2731_CUR_MASK ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static int sc2731_charger_get_current(struct sc2731_charger_info *info,
				      u32 *cur)
{
	int ret;
	u32 val;

	ret = regmap_read(info->regmap, info->base + SC2731_CHG_CFG1, &val);
	if (ret)
		return ret;

	val &= SC2731_CUR_MASK;
	*cur = val * SC2731_CURRENT_STEP + SC2731_CURRENT_PRECHG;

	return 0;
}