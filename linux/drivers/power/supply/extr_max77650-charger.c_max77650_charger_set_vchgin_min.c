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
struct max77650_charger_data {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX77650_CHARGER_VCHGIN_MIN_MASK ; 
 int /*<<< orphan*/  MAX77650_CHARGER_VCHGIN_MIN_SHIFT (int) ; 
 int /*<<< orphan*/  MAX77650_REG_CNFG_CHG_B ; 
 unsigned int* max77650_charger_vchgin_min_table ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77650_charger_set_vchgin_min(struct max77650_charger_data *chg,
					   unsigned int val)
{
	int i, rv;

	for (i = 0; i < ARRAY_SIZE(max77650_charger_vchgin_min_table); i++) {
		if (val == max77650_charger_vchgin_min_table[i]) {
			rv = regmap_update_bits(chg->map,
					MAX77650_REG_CNFG_CHG_B,
					MAX77650_CHARGER_VCHGIN_MIN_MASK,
					MAX77650_CHARGER_VCHGIN_MIN_SHIFT(i));
			if (rv)
				return rv;

			return 0;
		}
	}

	return -EINVAL;
}