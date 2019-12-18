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
struct rcar_du_plane_state {unsigned int hwindex; scalar_t__ source; TYPE_1__* format; } ;
struct rcar_du_group {int dummy; } ;
struct TYPE_2__ {int planes; scalar_t__ fourcc; int edf; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_NV12 ; 
 scalar_t__ DRM_FORMAT_NV21 ; 
 int /*<<< orphan*/  PnDDCR2 ; 
 int PnDDCR2_CODE ; 
 int PnDDCR2_DIVU ; 
 int PnDDCR2_DIVY ; 
 int PnDDCR2_NV21 ; 
 int PnDDCR2_Y420 ; 
 int /*<<< orphan*/  PnDDCR4 ; 
 int PnDDCR4_CODE ; 
 int PnDDCR4_VSPS ; 
 scalar_t__ RCAR_DU_PLANE_MEMORY ; 
 int /*<<< orphan*/  rcar_du_plane_setup_mode (struct rcar_du_group*,unsigned int,struct rcar_du_plane_state const*) ; 
 int /*<<< orphan*/  rcar_du_plane_write (struct rcar_du_group*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_du_plane_setup_format_gen2(struct rcar_du_group *rgrp,
					    unsigned int index,
					    const struct rcar_du_plane_state *state)
{
	u32 ddcr2 = PnDDCR2_CODE;
	u32 ddcr4;

	/*
	 * Data format
	 *
	 * The data format is selected by the DDDF field in PnMR and the EDF
	 * field in DDCR4.
	 */

	rcar_du_plane_setup_mode(rgrp, index, state);

	if (state->format->planes == 2) {
		if (state->hwindex != index) {
			if (state->format->fourcc == DRM_FORMAT_NV12 ||
			    state->format->fourcc == DRM_FORMAT_NV21)
				ddcr2 |= PnDDCR2_Y420;

			if (state->format->fourcc == DRM_FORMAT_NV21)
				ddcr2 |= PnDDCR2_NV21;

			ddcr2 |= PnDDCR2_DIVU;
		} else {
			ddcr2 |= PnDDCR2_DIVY;
		}
	}

	rcar_du_plane_write(rgrp, index, PnDDCR2, ddcr2);

	ddcr4 = state->format->edf | PnDDCR4_CODE;
	if (state->source != RCAR_DU_PLANE_MEMORY)
		ddcr4 |= PnDDCR4_VSPS;

	rcar_du_plane_write(rgrp, index, PnDDCR4, ddcr4);
}