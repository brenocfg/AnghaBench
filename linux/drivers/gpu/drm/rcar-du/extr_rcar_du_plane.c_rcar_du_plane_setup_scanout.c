#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_12__ {int x1; int y1; } ;
struct TYPE_10__ {TYPE_6__ src; struct drm_framebuffer* fb; TYPE_3__* crtc; } ;
struct rcar_du_plane_state {unsigned int hwindex; scalar_t__ source; TYPE_5__* format; TYPE_4__ state; } ;
struct rcar_du_group {int dummy; } ;
struct drm_gem_cma_object {unsigned int paddr; } ;
struct drm_framebuffer {unsigned int* pitches; unsigned int* offsets; } ;
struct TYPE_11__ {int planes; int bpp; } ;
struct TYPE_9__ {TYPE_2__* state; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_8__ {TYPE_1__ adjusted_mode; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  PnDSA0R ; 
 int /*<<< orphan*/  PnMWR ; 
 int /*<<< orphan*/  PnSPXR ; 
 int /*<<< orphan*/  PnSPYR ; 
 scalar_t__ RCAR_DU_PLANE_MEMORY ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,unsigned int) ; 
 int drm_rect_width (TYPE_6__*) ; 
 int /*<<< orphan*/  rcar_du_plane_write (struct rcar_du_group*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void rcar_du_plane_setup_scanout(struct rcar_du_group *rgrp,
					const struct rcar_du_plane_state *state)
{
	unsigned int src_x = state->state.src.x1 >> 16;
	unsigned int src_y = state->state.src.y1 >> 16;
	unsigned int index = state->hwindex;
	unsigned int pitch;
	bool interlaced;
	u32 dma[2];

	interlaced = state->state.crtc->state->adjusted_mode.flags
		   & DRM_MODE_FLAG_INTERLACE;

	if (state->source == RCAR_DU_PLANE_MEMORY) {
		struct drm_framebuffer *fb = state->state.fb;
		struct drm_gem_cma_object *gem;
		unsigned int i;

		if (state->format->planes == 2)
			pitch = fb->pitches[0];
		else
			pitch = fb->pitches[0] * 8 / state->format->bpp;

		for (i = 0; i < state->format->planes; ++i) {
			gem = drm_fb_cma_get_gem_obj(fb, i);
			dma[i] = gem->paddr + fb->offsets[i];
		}
	} else {
		pitch = drm_rect_width(&state->state.src) >> 16;
		dma[0] = 0;
		dma[1] = 0;
	}

	/*
	 * Memory pitch (expressed in pixels). Must be doubled for interlaced
	 * operation with 32bpp formats.
	 */
	rcar_du_plane_write(rgrp, index, PnMWR,
			    (interlaced && state->format->bpp == 32) ?
			    pitch * 2 : pitch);

	/*
	 * The Y position is expressed in raster line units and must be doubled
	 * for 32bpp formats, according to the R8A7790 datasheet. No mention of
	 * doubling the Y position is found in the R8A7779 datasheet, but the
	 * rule seems to apply there as well.
	 *
	 * Despite not being documented, doubling seem not to be needed when
	 * operating in interlaced mode.
	 *
	 * Similarly, for the second plane, NV12 and NV21 formats seem to
	 * require a halved Y position value, in both progressive and interlaced
	 * modes.
	 */
	rcar_du_plane_write(rgrp, index, PnSPXR, src_x);
	rcar_du_plane_write(rgrp, index, PnSPYR, src_y *
			    (!interlaced && state->format->bpp == 32 ? 2 : 1));

	rcar_du_plane_write(rgrp, index, PnDSA0R, dma[0]);

	if (state->format->planes == 2) {
		index = (index + 1) % 8;

		rcar_du_plane_write(rgrp, index, PnMWR, pitch);

		rcar_du_plane_write(rgrp, index, PnSPXR, src_x);
		rcar_du_plane_write(rgrp, index, PnSPYR, src_y *
				    (state->format->bpp == 16 ? 2 : 1) / 2);

		rcar_du_plane_write(rgrp, index, PnDSA0R, dma[1]);
	}
}