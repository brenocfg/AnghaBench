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
struct vibra_info {int enabled; int /*<<< orphan*/  base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDO_VIBR_PD ; 
 int /*<<< orphan*/  SLP_LDOVIBR_PD_EN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc27xx_vibra_set(struct vibra_info *info, bool on)
{
	if (on) {
		regmap_update_bits(info->regmap, info->base, LDO_VIBR_PD, 0);
		regmap_update_bits(info->regmap, info->base,
				   SLP_LDOVIBR_PD_EN, 0);
		info->enabled = true;
	} else {
		regmap_update_bits(info->regmap, info->base, LDO_VIBR_PD,
				   LDO_VIBR_PD);
		regmap_update_bits(info->regmap, info->base,
				   SLP_LDOVIBR_PD_EN, SLP_LDOVIBR_PD_EN);
		info->enabled = false;
	}
}