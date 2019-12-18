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
struct bd70528_psy {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned int BD70528_MASK_CHG_CHG_CURR ; 
 int /*<<< orphan*/  BD70528_REG_CHG_CHG_CURR_WARM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int find_value_for_selector_low (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/ * warm_charge_curr ; 

__attribute__((used)) static int get_charge_current(struct bd70528_psy *bdpsy, int *ma)
{
	unsigned int sel;
	int ret;

	ret = regmap_read(bdpsy->regmap, BD70528_REG_CHG_CHG_CURR_WARM,
			  &sel);
	if (ret) {
		dev_err(bdpsy->dev,
			"Charge current reading failed (%d)\n", ret);
		return ret;
	}

	sel &= BD70528_MASK_CHG_CHG_CURR;

	ret = find_value_for_selector_low(&warm_charge_curr[0],
					  ARRAY_SIZE(warm_charge_curr), sel,
					  ma);
	if (ret) {
		dev_err(bdpsy->dev,
			"Unknown charge current value 0x%x\n",
			sel);
	}

	return ret;
}