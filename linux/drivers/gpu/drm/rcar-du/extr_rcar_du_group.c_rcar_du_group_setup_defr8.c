#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rcar_du_group {int index; struct rcar_du_device* dev; } ;
struct rcar_du_device {int dpad0_source; int vspd1_sink; TYPE_1__* info; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFR8 ; 
 int /*<<< orphan*/  DEFR8_CODE ; 
 int /*<<< orphan*/  DEFR8_DEFE8 ; 
 int /*<<< orphan*/  DEFR8_DRGBS_DU (int) ; 
 int /*<<< orphan*/  DEFR8_VSCS ; 
 int /*<<< orphan*/  rcar_du_group_write (struct rcar_du_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_du_group_setup_defr8(struct rcar_du_group *rgrp)
{
	struct rcar_du_device *rcdu = rgrp->dev;
	u32 defr8 = DEFR8_CODE;

	if (rcdu->info->gen < 3) {
		defr8 |= DEFR8_DEFE8;

		/*
		 * On Gen2 the DEFR8 register for the first group also controls
		 * RGB output routing to DPAD0 and VSPD1 routing to DU0/1/2 for
		 * DU instances that support it.
		 */
		if (rgrp->index == 0) {
			defr8 |= DEFR8_DRGBS_DU(rcdu->dpad0_source);
			if (rgrp->dev->vspd1_sink == 2)
				defr8 |= DEFR8_VSCS;
		}
	} else {
		/*
		 * On Gen3 VSPD routing can't be configured, and DPAD routing
		 * is set in the group corresponding to the DPAD output (no Gen3
		 * SoC has multiple DPAD sources belonging to separate groups).
		 */
		if (rgrp->index == rcdu->dpad0_source / 2)
			defr8 |= DEFR8_DRGBS_DU(rcdu->dpad0_source);
	}

	rcar_du_group_write(rgrp, DEFR8, defr8);
}