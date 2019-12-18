#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void** dotclkin; void* extal; void* mod; } ;
struct rcar_lvds {int /*<<< orphan*/  dev; TYPE_2__ clocks; TYPE_1__* info; } ;
struct TYPE_3__ {int quirks; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int RCAR_LVDS_QUIRK_EXT_PLL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* rcar_lvds_get_clock (struct rcar_lvds*,char*,int) ; 

__attribute__((used)) static int rcar_lvds_get_clocks(struct rcar_lvds *lvds)
{
	lvds->clocks.mod = rcar_lvds_get_clock(lvds, NULL, false);
	if (IS_ERR(lvds->clocks.mod))
		return PTR_ERR(lvds->clocks.mod);

	/*
	 * LVDS encoders without an extended PLL have no external clock inputs.
	 */
	if (!(lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL))
		return 0;

	lvds->clocks.extal = rcar_lvds_get_clock(lvds, "extal", true);
	if (IS_ERR(lvds->clocks.extal))
		return PTR_ERR(lvds->clocks.extal);

	lvds->clocks.dotclkin[0] = rcar_lvds_get_clock(lvds, "dclkin.0", true);
	if (IS_ERR(lvds->clocks.dotclkin[0]))
		return PTR_ERR(lvds->clocks.dotclkin[0]);

	lvds->clocks.dotclkin[1] = rcar_lvds_get_clock(lvds, "dclkin.1", true);
	if (IS_ERR(lvds->clocks.dotclkin[1]))
		return PTR_ERR(lvds->clocks.dotclkin[1]);

	/* At least one input to the PLL must be available. */
	if (!lvds->clocks.extal && !lvds->clocks.dotclkin[0] &&
	    !lvds->clocks.dotclkin[1]) {
		dev_err(lvds->dev,
			"no input clock (extal, dclkin.0 or dclkin.1)\n");
		return -EINVAL;
	}

	return 0;
}