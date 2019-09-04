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
typedef  int u8 ;
struct ak8974 {int /*<<< orphan*/  map; int /*<<< orphan*/  drdy_complete; int /*<<< orphan*/  drdy_active_low; scalar_t__ drdy_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK8974_CTRL2 ; 
 int AK8974_CTRL2_DRDY_EN ; 
 int AK8974_CTRL2_DRDY_POL ; 
 int AK8974_CTRL2_INT_EN ; 
 int /*<<< orphan*/  AK8974_CTRL3 ; 
 int AK8974_CTRL3_FORCE ; 
 int /*<<< orphan*/  AK8974_INT_CLEAR ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ak8974_trigmeas(struct ak8974 *ak8974)
{
	unsigned int clear;
	u8 mask;
	u8 val;
	int ret;

	/* Clear any previous measurement overflow status */
	ret = regmap_read(ak8974->map, AK8974_INT_CLEAR, &clear);
	if (ret)
		return ret;

	/* If we have a DRDY IRQ line, use it */
	if (ak8974->drdy_irq) {
		mask = AK8974_CTRL2_INT_EN |
			AK8974_CTRL2_DRDY_EN |
			AK8974_CTRL2_DRDY_POL;
		val = AK8974_CTRL2_DRDY_EN;

		if (!ak8974->drdy_active_low)
			val |= AK8974_CTRL2_DRDY_POL;

		init_completion(&ak8974->drdy_complete);
		ret = regmap_update_bits(ak8974->map, AK8974_CTRL2,
					 mask, val);
		if (ret)
			return ret;
	}

	/* Force a measurement */
	return regmap_update_bits(ak8974->map,
				  AK8974_CTRL3,
				  AK8974_CTRL3_FORCE,
				  AK8974_CTRL3_FORCE);
}