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
struct rcar_du_plane_state {int hwindex; scalar_t__ source; TYPE_2__* format; } ;
struct rcar_du_group {scalar_t__ index; struct rcar_du_device* dev; } ;
struct rcar_du_device {unsigned int vspd1_sink; TYPE_1__* info; } ;
struct TYPE_4__ {int planes; } ;
struct TYPE_3__ {int gen; } ;

/* Variables and functions */
 scalar_t__ RCAR_DU_PLANE_VSPD1 ; 
 int /*<<< orphan*/  rcar_du_plane_setup_format (struct rcar_du_group*,int,struct rcar_du_plane_state const*) ; 
 int /*<<< orphan*/  rcar_du_plane_setup_scanout (struct rcar_du_group*,struct rcar_du_plane_state const*) ; 
 int /*<<< orphan*/  rcar_du_set_dpad0_vsp1_routing (struct rcar_du_device*) ; 

void __rcar_du_plane_setup(struct rcar_du_group *rgrp,
			   const struct rcar_du_plane_state *state)
{
	struct rcar_du_device *rcdu = rgrp->dev;

	rcar_du_plane_setup_format(rgrp, state->hwindex, state);
	if (state->format->planes == 2)
		rcar_du_plane_setup_format(rgrp, (state->hwindex + 1) % 8,
					   state);

	if (rcdu->info->gen < 3)
		rcar_du_plane_setup_scanout(rgrp, state);

	if (state->source == RCAR_DU_PLANE_VSPD1) {
		unsigned int vspd1_sink = rgrp->index ? 2 : 0;

		if (rcdu->vspd1_sink != vspd1_sink) {
			rcdu->vspd1_sink = vspd1_sink;
			rcar_du_set_dpad0_vsp1_routing(rcdu);
		}
	}
}