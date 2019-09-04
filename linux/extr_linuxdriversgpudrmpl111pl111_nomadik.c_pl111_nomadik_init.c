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
struct regmap {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  PMU_CTRL_LCDNDIF ; 
 int /*<<< orphan*/  PMU_CTRL_OFFSET ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regmap* syscon_regmap_lookup_by_compatible (char*) ; 

void pl111_nomadik_init(struct device *dev)
{
	struct regmap *pmu_regmap;

	/*
	 * Just bail out of this is not found, we could be running
	 * multiplatform on something else than Nomadik.
	 */
	pmu_regmap =
		syscon_regmap_lookup_by_compatible("stericsson,nomadik-pmu");
	if (IS_ERR(pmu_regmap))
		return;

	/*
	 * This bit in the PMU controller multiplexes the two graphics
	 * blocks found in the Nomadik STn8815. The other one is called
	 * MDIF (Master Display Interface) and gets muxed out here.
	 */
	regmap_update_bits(pmu_regmap,
			   PMU_CTRL_OFFSET,
			   PMU_CTRL_LCDNDIF,
			   0);
	dev_info(dev, "set Nomadik PMU mux to CLCD mode\n");
}