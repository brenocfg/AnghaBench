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
struct regulator_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32MP1_SYSCFG_EN_BOOSTER_MASK ; 
 int /*<<< orphan*/  STM32MP1_SYSCFG_PMCCLRR ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32mp1_booster_disable(struct regulator_dev *rdev)
{
	return regmap_write(rdev->regmap, STM32MP1_SYSCFG_PMCCLRR,
			    STM32MP1_SYSCFG_EN_BOOSTER_MASK);
}