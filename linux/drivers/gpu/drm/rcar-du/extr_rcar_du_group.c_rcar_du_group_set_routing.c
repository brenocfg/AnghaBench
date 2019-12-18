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
typedef  int u32 ;
struct rcar_du_group {int index; struct rcar_du_device* dev; } ;
struct rcar_du_device {int dpad1_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORCR ; 
 int DORCR_DK2S ; 
 int DORCR_PG2D_DS1 ; 
 int DORCR_PG2D_DS2 ; 
 int DORCR_PG2D_MASK ; 
 int DORCR_PG2T ; 
 int rcar_du_group_read (struct rcar_du_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_group_set_dpad_levels (struct rcar_du_group*) ; 
 int /*<<< orphan*/  rcar_du_group_write (struct rcar_du_group*,int /*<<< orphan*/ ,int) ; 
 int rcar_du_set_dpad0_vsp1_routing (struct rcar_du_device*) ; 

int rcar_du_group_set_routing(struct rcar_du_group *rgrp)
{
	struct rcar_du_device *rcdu = rgrp->dev;
	u32 dorcr = rcar_du_group_read(rgrp, DORCR);

	dorcr &= ~(DORCR_PG2T | DORCR_DK2S | DORCR_PG2D_MASK);

	/*
	 * Set the DPAD1 pins sources. Select CRTC 0 if explicitly requested and
	 * CRTC 1 in all other cases to avoid cloning CRTC 0 to DPAD0 and DPAD1
	 * by default.
	 */
	if (rcdu->dpad1_source == rgrp->index * 2)
		dorcr |= DORCR_PG2D_DS1;
	else
		dorcr |= DORCR_PG2T | DORCR_DK2S | DORCR_PG2D_DS2;

	rcar_du_group_write(rgrp, DORCR, dorcr);

	rcar_du_group_set_dpad_levels(rgrp);

	return rcar_du_set_dpad0_vsp1_routing(rgrp->dev);
}