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
struct rcar_du_group {int index; struct rcar_du_device* dev; } ;
struct rcar_du_device {struct rcar_du_crtc* crtcs; TYPE_1__* info; } ;
struct rcar_du_crtc {int dummy; } ;
struct TYPE_2__ {int channels_mask; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DSYSR ; 
 int DSYSR_DEN ; 
 int DSYSR_DRES ; 
 int /*<<< orphan*/  rcar_du_crtc_dsysr_clr_set (struct rcar_du_crtc*,int,int) ; 
 int /*<<< orphan*/  rcar_du_group_write (struct rcar_du_group*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __rcar_du_group_start_stop(struct rcar_du_group *rgrp, bool start)
{
	struct rcar_du_device *rcdu = rgrp->dev;

	/*
	 * Group start/stop is controlled by the DRES and DEN bits of DSYSR0
	 * for the first group and DSYSR2 for the second group. On most DU
	 * instances, this maps to the first CRTC of the group, and we can just
	 * use rcar_du_crtc_dsysr_clr_set() to access the correct DSYSR. On
	 * M3-N, however, DU2 doesn't exist, but DSYSR2 does. We thus need to
	 * access the register directly using group read/write.
	 */
	if (rcdu->info->channels_mask & BIT(rgrp->index * 2)) {
		struct rcar_du_crtc *rcrtc = &rgrp->dev->crtcs[rgrp->index * 2];

		rcar_du_crtc_dsysr_clr_set(rcrtc, DSYSR_DRES | DSYSR_DEN,
					   start ? DSYSR_DEN : DSYSR_DRES);
	} else {
		rcar_du_group_write(rgrp, DSYSR,
				    start ? DSYSR_DEN : DSYSR_DRES);
	}
}