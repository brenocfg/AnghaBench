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
struct rcar_du_group {scalar_t__ used_crtcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rcar_du_group_start_stop (struct rcar_du_group*,int) ; 

void rcar_du_group_start_stop(struct rcar_du_group *rgrp, bool start)
{
	/*
	 * Many of the configuration bits are only updated when the display
	 * reset (DRES) bit in DSYSR is set to 1, disabling *both* CRTCs. Some
	 * of those bits could be pre-configured, but others (especially the
	 * bits related to plane assignment to display timing controllers) need
	 * to be modified at runtime.
	 *
	 * Restart the display controller if a start is requested. Sorry for the
	 * flicker. It should be possible to move most of the "DRES-update" bits
	 * setup to driver initialization time and minimize the number of cases
	 * when the display controller will have to be restarted.
	 */
	if (start) {
		if (rgrp->used_crtcs++ != 0)
			__rcar_du_group_start_stop(rgrp, false);
		__rcar_du_group_start_stop(rgrp, true);
	} else {
		if (--rgrp->used_crtcs == 0)
			__rcar_du_group_start_stop(rgrp, false);
	}
}