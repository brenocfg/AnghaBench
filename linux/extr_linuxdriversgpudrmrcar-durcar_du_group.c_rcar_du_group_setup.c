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
struct rcar_du_group {scalar_t__ index; int num_crtcs; int dptsr_planes; int /*<<< orphan*/  lock; struct rcar_du_device* dev; } ;
struct rcar_du_device {TYPE_1__* info; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFR ; 
 int /*<<< orphan*/  DEFR10 ; 
 int DEFR10_CODE ; 
 int DEFR10_DEFE10 ; 
 int /*<<< orphan*/  DEFR2 ; 
 int DEFR2_CODE ; 
 int DEFR2_DEFE2G ; 
 int /*<<< orphan*/  DEFR3 ; 
 int DEFR3_CODE ; 
 int DEFR3_DEFE3 ; 
 int /*<<< orphan*/  DEFR4 ; 
 int DEFR4_CODE ; 
 int /*<<< orphan*/  DEFR5 ; 
 int DEFR5_CODE ; 
 int DEFR5_DEFE5 ; 
 int DEFR_CODE ; 
 int DEFR_DEFE ; 
 int /*<<< orphan*/  DIDSR ; 
 int DIDSR_CODE ; 
 int /*<<< orphan*/  DORCR ; 
 int DORCR_DPRS ; 
 int DORCR_PG1D_DS1 ; 
 int /*<<< orphan*/  DPTSR ; 
 int /*<<< orphan*/  RCAR_DU_FEATURE_EXT_CTRL_REGS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcar_du_group_setup_defr8 (struct rcar_du_group*) ; 
 int /*<<< orphan*/  rcar_du_group_setup_pins (struct rcar_du_group*) ; 
 int /*<<< orphan*/  rcar_du_group_write (struct rcar_du_group*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rcar_du_has (struct rcar_du_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_du_group_setup(struct rcar_du_group *rgrp)
{
	struct rcar_du_device *rcdu = rgrp->dev;

	/* Enable extended features */
	rcar_du_group_write(rgrp, DEFR, DEFR_CODE | DEFR_DEFE);
	if (rcdu->info->gen < 3) {
		rcar_du_group_write(rgrp, DEFR2, DEFR2_CODE | DEFR2_DEFE2G);
		rcar_du_group_write(rgrp, DEFR3, DEFR3_CODE | DEFR3_DEFE3);
		rcar_du_group_write(rgrp, DEFR4, DEFR4_CODE);
	}
	rcar_du_group_write(rgrp, DEFR5, DEFR5_CODE | DEFR5_DEFE5);

	rcar_du_group_setup_pins(rgrp);

	if (rcar_du_has(rgrp->dev, RCAR_DU_FEATURE_EXT_CTRL_REGS)) {
		rcar_du_group_setup_defr8(rgrp);

		/*
		 * Configure input dot clock routing. We currently hardcode the
		 * configuration to routing DOTCLKINn to DUn. Register fields
		 * depend on the DU generation, but the resulting value is 0 in
		 * all cases.
		 *
		 * On Gen2 a single register in the first group controls dot
		 * clock selection for all channels, while on Gen3 dot clocks
		 * are setup through per-group registers, only available when
		 * the group has two channels.
		 */
		if ((rcdu->info->gen < 3 && rgrp->index == 0) ||
		    (rcdu->info->gen == 3 &&  rgrp->num_crtcs > 1))
			rcar_du_group_write(rgrp, DIDSR, DIDSR_CODE);
	}

	if (rcdu->info->gen >= 3)
		rcar_du_group_write(rgrp, DEFR10, DEFR10_CODE | DEFR10_DEFE10);

	/*
	 * Use DS1PR and DS2PR to configure planes priorities and connects the
	 * superposition 0 to DU0 pins. DU1 pins will be configured dynamically.
	 */
	rcar_du_group_write(rgrp, DORCR, DORCR_PG1D_DS1 | DORCR_DPRS);

	/* Apply planes to CRTCs association. */
	mutex_lock(&rgrp->lock);
	rcar_du_group_write(rgrp, DPTSR, (rgrp->dptsr_planes << 16) |
			    rgrp->dptsr_planes);
	mutex_unlock(&rgrp->lock);
}