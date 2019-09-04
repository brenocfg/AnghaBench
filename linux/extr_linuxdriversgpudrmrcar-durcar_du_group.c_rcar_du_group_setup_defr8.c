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
typedef  int /*<<< orphan*/  u32 ;
struct rcar_du_group {scalar_t__ index; struct rcar_du_device* dev; } ;
struct rcar_du_device {int dpad0_source; int vspd1_sink; struct rcar_du_crtc* crtcs; TYPE_2__* info; } ;
struct rcar_du_crtc {int index; } ;
struct TYPE_4__ {int gen; TYPE_1__* routes; } ;
struct TYPE_3__ {unsigned int possible_crtcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFR8 ; 
 int /*<<< orphan*/  DEFR8_CODE ; 
 int /*<<< orphan*/  DEFR8_DEFE8 ; 
 int /*<<< orphan*/  DEFR8_DRGBS_DU (int) ; 
 int /*<<< orphan*/  DEFR8_VSCS ; 
 size_t RCAR_DU_OUTPUT_DPAD0 ; 
 int ffs (unsigned int) ; 
 int /*<<< orphan*/  rcar_du_group_write (struct rcar_du_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_du_group_setup_defr8(struct rcar_du_group *rgrp)
{
	struct rcar_du_device *rcdu = rgrp->dev;
	unsigned int possible_crtcs =
		rcdu->info->routes[RCAR_DU_OUTPUT_DPAD0].possible_crtcs;
	u32 defr8 = DEFR8_CODE;

	if (rcdu->info->gen < 3) {
		defr8 |= DEFR8_DEFE8;

		/*
		 * On Gen2 the DEFR8 register for the first group also controls
		 * RGB output routing to DPAD0 and VSPD1 routing to DU0/1/2 for
		 * DU instances that support it.
		 */
		if (rgrp->index == 0) {
			if (possible_crtcs > 1)
				defr8 |= DEFR8_DRGBS_DU(rcdu->dpad0_source);
			if (rgrp->dev->vspd1_sink == 2)
				defr8 |= DEFR8_VSCS;
		}
	} else {
		/*
		 * On Gen3 VSPD routing can't be configured, but DPAD routing
		 * needs to be set despite having a single option available.
		 */
		unsigned int rgb_crtc = ffs(possible_crtcs) - 1;
		struct rcar_du_crtc *crtc = &rcdu->crtcs[rgb_crtc];

		if (crtc->index / 2 == rgrp->index)
			defr8 |= DEFR8_DRGBS_DU(crtc->index);
	}

	rcar_du_group_write(rgrp, DEFR8, defr8);
}