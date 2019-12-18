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
struct rcar_du_group {int dummy; } ;
struct rcar_du_device {struct rcar_du_crtc* crtcs; struct rcar_du_group* groups; int /*<<< orphan*/  num_crtcs; TYPE_1__* info; } ;
struct rcar_du_crtc {int /*<<< orphan*/  clock; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_group_setup_defr8 (struct rcar_du_group*) ; 

int rcar_du_set_dpad0_vsp1_routing(struct rcar_du_device *rcdu)
{
	struct rcar_du_group *rgrp;
	struct rcar_du_crtc *crtc;
	unsigned int index;
	int ret;

	if (rcdu->info->gen < 2)
		return 0;

	/*
	 * RGB output routing to DPAD0 and VSP1D routing to DU0/1/2 are
	 * configured in the DEFR8 register of the first group on Gen2 and the
	 * last group on Gen3. As this function can be called with the DU
	 * channels of the corresponding CRTCs disabled, we need to enable the
	 * group clock before accessing the register.
	 */
	index = rcdu->info->gen < 3 ? 0 : DIV_ROUND_UP(rcdu->num_crtcs, 2) - 1;
	rgrp = &rcdu->groups[index];
	crtc = &rcdu->crtcs[index * 2];

	ret = clk_prepare_enable(crtc->clock);
	if (ret < 0)
		return ret;

	rcar_du_group_setup_defr8(rgrp);

	clk_disable_unprepare(crtc->clock);

	return 0;
}