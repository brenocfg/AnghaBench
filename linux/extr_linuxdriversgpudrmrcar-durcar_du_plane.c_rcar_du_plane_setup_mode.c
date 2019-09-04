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
typedef  int u32 ;
struct TYPE_3__ {int alpha; } ;
struct rcar_du_plane_state {int colorkey; TYPE_2__* format; TYPE_1__ state; } ;
struct rcar_du_group {int dummy; } ;
struct TYPE_4__ {int fourcc; int pnmr; } ;

/* Variables and functions */
#define  DRM_FORMAT_ARGB1555 132 
#define  DRM_FORMAT_ARGB8888 131 
#define  DRM_FORMAT_RGB565 130 
#define  DRM_FORMAT_XRGB1555 129 
#define  DRM_FORMAT_XRGB8888 128 
 int DRM_FORMAT_YUYV ; 
 int /*<<< orphan*/  PnALPHAR ; 
 int PnALPHAR_ABIT_0 ; 
 int PnALPHAR_ABIT_X ; 
 int /*<<< orphan*/  PnMR ; 
 int PnMR_BM_MD ; 
 int PnMR_SPIM_TP_OFF ; 
 int PnMR_YCDF_YUYV ; 
 int /*<<< orphan*/  PnTC2R ; 
 int /*<<< orphan*/  PnTC3R ; 
 int PnTC3R_CODE ; 
 int RCAR_DU_COLORKEY_MASK ; 
 int RCAR_DU_COLORKEY_NONE ; 
 int /*<<< orphan*/  rcar_du_plane_write (struct rcar_du_group*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_du_plane_setup_mode(struct rcar_du_group *rgrp,
				     unsigned int index,
				     const struct rcar_du_plane_state *state)
{
	u32 colorkey;
	u32 pnmr;

	/*
	 * The PnALPHAR register controls alpha-blending in 16bpp formats
	 * (ARGB1555 and XRGB1555).
	 *
	 * For ARGB, set the alpha value to 0, and enable alpha-blending when
	 * the A bit is 0. This maps A=0 to alpha=0 and A=1 to alpha=255.
	 *
	 * For XRGB, set the alpha value to the plane-wide alpha value and
	 * enable alpha-blending regardless of the X bit value.
	 */
	if (state->format->fourcc != DRM_FORMAT_XRGB1555)
		rcar_du_plane_write(rgrp, index, PnALPHAR, PnALPHAR_ABIT_0);
	else
		rcar_du_plane_write(rgrp, index, PnALPHAR,
				    PnALPHAR_ABIT_X | state->state.alpha >> 8);

	pnmr = PnMR_BM_MD | state->format->pnmr;

	/*
	 * Disable color keying when requested. YUV formats have the
	 * PnMR_SPIM_TP_OFF bit set in their pnmr field, disabling color keying
	 * automatically.
	 */
	if ((state->colorkey & RCAR_DU_COLORKEY_MASK) == RCAR_DU_COLORKEY_NONE)
		pnmr |= PnMR_SPIM_TP_OFF;

	/* For packed YUV formats we need to select the U/V order. */
	if (state->format->fourcc == DRM_FORMAT_YUYV)
		pnmr |= PnMR_YCDF_YUYV;

	rcar_du_plane_write(rgrp, index, PnMR, pnmr);

	switch (state->format->fourcc) {
	case DRM_FORMAT_RGB565:
		colorkey = ((state->colorkey & 0xf80000) >> 8)
			 | ((state->colorkey & 0x00fc00) >> 5)
			 | ((state->colorkey & 0x0000f8) >> 3);
		rcar_du_plane_write(rgrp, index, PnTC2R, colorkey);
		break;

	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_XRGB1555:
		colorkey = ((state->colorkey & 0xf80000) >> 9)
			 | ((state->colorkey & 0x00f800) >> 6)
			 | ((state->colorkey & 0x0000f8) >> 3);
		rcar_du_plane_write(rgrp, index, PnTC2R, colorkey);
		break;

	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
		rcar_du_plane_write(rgrp, index, PnTC3R,
				    PnTC3R_CODE | (state->colorkey & 0xffffff));
		break;
	}
}