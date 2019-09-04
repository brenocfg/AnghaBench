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
typedef  int u32 ;
struct rcar_du_group {int index; TYPE_1__* dev; } ;
struct rcar_du_crtc {int outputs; } ;
struct TYPE_2__ {struct rcar_du_crtc* crtcs; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DORCR ; 
 int DORCR_DK2S ; 
 int DORCR_PG2D_DS1 ; 
 int DORCR_PG2D_DS2 ; 
 int DORCR_PG2D_MASK ; 
 int DORCR_PG2T ; 
 int /*<<< orphan*/  RCAR_DU_OUTPUT_DPAD1 ; 
 int rcar_du_group_read (struct rcar_du_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_group_write (struct rcar_du_group*,int /*<<< orphan*/ ,int) ; 
 int rcar_du_set_dpad0_vsp1_routing (TYPE_1__*) ; 

int rcar_du_group_set_routing(struct rcar_du_group *rgrp)
{
	struct rcar_du_crtc *crtc0 = &rgrp->dev->crtcs[rgrp->index * 2];
	u32 dorcr = rcar_du_group_read(rgrp, DORCR);

	dorcr &= ~(DORCR_PG2T | DORCR_DK2S | DORCR_PG2D_MASK);

	/*
	 * Set the DPAD1 pins sources. Select CRTC 0 if explicitly requested and
	 * CRTC 1 in all other cases to avoid cloning CRTC 0 to DPAD0 and DPAD1
	 * by default.
	 */
	if (crtc0->outputs & BIT(RCAR_DU_OUTPUT_DPAD1))
		dorcr |= DORCR_PG2D_DS1;
	else
		dorcr |= DORCR_PG2T | DORCR_DK2S | DORCR_PG2D_DS2;

	rcar_du_group_write(rgrp, DORCR, dorcr);

	return rcar_du_set_dpad0_vsp1_routing(rgrp->dev);
}