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
struct ak8974 {scalar_t__ variant; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK8974_CTRL2 ; 
 int AK8974_CTRL2_DRDY_EN ; 
 int AK8974_CTRL2_INT_EN ; 
 int /*<<< orphan*/  AK8974_CTRL3 ; 
 int /*<<< orphan*/  AK8974_INT_CTRL ; 
 int AK8974_INT_CTRL_POL ; 
 int /*<<< orphan*/  AK8974_PRESET ; 
 scalar_t__ AK8974_WHOAMI_VALUE_AMI306 ; 
 int /*<<< orphan*/  AMI306_CTRL4 ; 
 int ak8974_set_u16_val (struct ak8974*,int /*<<< orphan*/ ,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ak8974_configure(struct ak8974 *ak8974)
{
	int ret;

	ret = regmap_write(ak8974->map, AK8974_CTRL2, AK8974_CTRL2_DRDY_EN |
			   AK8974_CTRL2_INT_EN);
	if (ret)
		return ret;
	ret = regmap_write(ak8974->map, AK8974_CTRL3, 0);
	if (ret)
		return ret;
	if (ak8974->variant == AK8974_WHOAMI_VALUE_AMI306) {
		/* magic from datasheet: set high-speed measurement mode */
		ret = ak8974_set_u16_val(ak8974, AMI306_CTRL4, 0xA07E);
		if (ret)
			return ret;
	}
	ret = regmap_write(ak8974->map, AK8974_INT_CTRL, AK8974_INT_CTRL_POL);
	if (ret)
		return ret;

	return regmap_write(ak8974->map, AK8974_PRESET, 0);
}