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
struct madera {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap_32bit; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs47l92_reva_16_patch ; 
 int /*<<< orphan*/  cs47l92_reva_32_patch ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cs47l92_patch(struct madera *madera)
{
	int ret;

	ret = regmap_register_patch(madera->regmap,
				    cs47l92_reva_16_patch,
				    ARRAY_SIZE(cs47l92_reva_16_patch));
	if (ret < 0) {
		dev_err(madera->dev,
			"Error in applying 16-bit patch: %d\n", ret);
		return ret;
	}

	ret = regmap_register_patch(madera->regmap_32bit,
				    cs47l92_reva_32_patch,
				    ARRAY_SIZE(cs47l92_reva_32_patch));
	if (ret < 0) {
		dev_err(madera->dev,
			"Error in applying 32-bit patch: %d\n", ret);
		return ret;
	}

	return 0;
}