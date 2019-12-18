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
struct bd70528_psy {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BD70528_MASK_CHG_DCIN_ILIM ; 
 int /*<<< orphan*/  BD70528_REG_CHG_DCIN_ILIM ; 
 int EINVAL ; 
 unsigned int MAX_CURR_LIMIT_SEL ; 
 unsigned int MIN_CURR_LIMIT_SEL ; 
 int /*<<< orphan*/ * current_limit_ranges ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int find_selector_for_value_low (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned int*,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int set_current_limit(struct bd70528_psy *bdpsy, int ma)
{
	unsigned int reg;
	int ret = 0, tmpret;
	bool found;

	if (ma > 500) {
		dev_warn(bdpsy->dev,
			 "Requested current limit %u exceed maximum (500mA)\n",
			 ma);
		reg = MAX_CURR_LIMIT_SEL;
		goto set;
	}
	if (ma < 5) {
		dev_err(bdpsy->dev,
			"Requested current limit %u smaller than min (5mA)\n",
			ma);
		reg = MIN_CURR_LIMIT_SEL;
		ret = -EINVAL;
		goto set;
	}

	ret = find_selector_for_value_low(&current_limit_ranges[0],
					  ARRAY_SIZE(current_limit_ranges), ma,
					  &reg, &found);
	if (ret) {
		reg = MIN_CURR_LIMIT_SEL;
		goto set;
	}
	if (!found) {
		/* There was a gap in supported values and we hit it ?*/
		dev_warn(bdpsy->dev, "Unsupported current limit %umA\n",
			 ma);
	}

set:
	tmpret = regmap_update_bits(bdpsy->regmap,
				    BD70528_REG_CHG_DCIN_ILIM,
				    BD70528_MASK_CHG_DCIN_ILIM, reg);

	if (!ret)
		ret = tmpret;

	return ret;
}