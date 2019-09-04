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
struct axp288_extcon_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP288_BC_GLOBAL_REG ; 
 int /*<<< orphan*/  BC_GLOBAL_RUN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axp288_extcon_enable(struct axp288_extcon_info *info)
{
	regmap_update_bits(info->regmap, AXP288_BC_GLOBAL_REG,
						BC_GLOBAL_RUN, 0);
	/* Enable the charger detection logic */
	regmap_update_bits(info->regmap, AXP288_BC_GLOBAL_REG,
					BC_GLOBAL_RUN, BC_GLOBAL_RUN);
}