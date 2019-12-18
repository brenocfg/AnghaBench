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
struct TYPE_2__ {int /*<<< orphan*/  regmap_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8907_MASK_POWER_OFF ; 
 int /*<<< orphan*/  MAX8907_REG_RESET_CNFG ; 
 TYPE_1__* max8907_pm_off ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max8907_power_off(void)
{
	regmap_update_bits(max8907_pm_off->regmap_gen, MAX8907_REG_RESET_CNFG,
			MAX8907_MASK_POWER_OFF, MAX8907_MASK_POWER_OFF);
}