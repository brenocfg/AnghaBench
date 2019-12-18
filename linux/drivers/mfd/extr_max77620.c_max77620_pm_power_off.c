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
struct max77620_chip {int /*<<< orphan*/  rmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX77620_ONOFFCNFG1_SFT_RST ; 
 int /*<<< orphan*/  MAX77620_REG_ONOFFCNFG1 ; 
 struct max77620_chip* max77620_scratch ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max77620_pm_power_off(void)
{
	struct max77620_chip *chip = max77620_scratch;

	regmap_update_bits(chip->rmap, MAX77620_REG_ONOFFCNFG1,
			   MAX77620_ONOFFCNFG1_SFT_RST,
			   MAX77620_ONOFFCNFG1_SFT_RST);
}