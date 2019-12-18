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
 unsigned int BD70528_MASK_CHG_DCIN_ILIM ; 
 int /*<<< orphan*/  BD70528_REG_CHG_DCIN_ILIM ; 
 int /*<<< orphan*/ * current_limit_ranges ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int find_value_for_selector_low (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int get_current_limit(struct bd70528_psy *bdpsy, int *ma)
{
	unsigned int sel;
	int ret;

	ret = regmap_read(bdpsy->regmap, BD70528_REG_CHG_DCIN_ILIM,
			  &sel);

	if (ret) {
		dev_err(bdpsy->dev,
			"Input current limit reading failed (%d)\n", ret);
		return ret;
	}

	sel &= BD70528_MASK_CHG_DCIN_ILIM;

	ret = find_value_for_selector_low(&current_limit_ranges[0],
					  ARRAY_SIZE(current_limit_ranges), sel,
					  ma);

	if (ret) {
		/* Unspecified values mean 500 mA */
		*ma = 500;
	}
	return 0;
}