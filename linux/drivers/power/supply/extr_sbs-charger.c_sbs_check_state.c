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
struct sbs_info {unsigned int last_state; int /*<<< orphan*/  power_supply; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBS_CHARGER_REG_STATUS ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int sbs_check_state(struct sbs_info *chip)
{
	unsigned int reg;
	int ret;

	ret = regmap_read(chip->regmap, SBS_CHARGER_REG_STATUS, &reg);
	if (!ret && reg != chip->last_state) {
		chip->last_state = reg;
		power_supply_changed(chip->power_supply);
		return 1;
	}

	return 0;
}