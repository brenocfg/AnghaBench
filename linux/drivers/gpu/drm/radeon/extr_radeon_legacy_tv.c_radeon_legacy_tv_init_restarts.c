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
typedef  scalar_t__ u16 ;
struct radeon_tv_mode_constants {unsigned int hor_total; unsigned int ver_total; int def_restart; int hor_resolution; scalar_t__ pix_to_tv; } ;
struct TYPE_2__ {scalar_t__* h_code_timing; int hrestart; int vrestart; int frestart; int timing_cntl; } ;
struct radeon_encoder_tv_dac {scalar_t__ tv_std; int h_pos; int v_pos; int h_size; TYPE_1__ tv; } ;
struct radeon_encoder {struct radeon_encoder_tv_dac* enc_priv; } ;
struct drm_encoder {int dummy; } ;
typedef  scalar_t__ PAL_TV_H_SIZE_UNIT ;
typedef  scalar_t__ NTSC_TV_H_SIZE_UNIT ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,scalar_t__,...) ; 
 int H_POS_UNIT ; 
 size_t H_TABLE_POS1 ; 
 size_t H_TABLE_POS2 ; 
 int NTSC_TV_CLOCK_T ; 
 scalar_t__ NTSC_TV_LINES_PER_FRAME ; 
 int NTSC_TV_VFTOTAL ; 
 scalar_t__ NTSC_TV_ZERO_H_SIZE ; 
 int PAL_TV_CLOCK_T ; 
 scalar_t__ PAL_TV_LINES_PER_FRAME ; 
 int PAL_TV_VFTOTAL ; 
 scalar_t__ PAL_TV_ZERO_H_SIZE ; 
 int RADEON_H_INC_MASK ; 
 int RADEON_H_INC_SHIFT ; 
 scalar_t__ TV_STD_NTSC ; 
 scalar_t__ TV_STD_NTSC_J ; 
 scalar_t__ TV_STD_PAL_60 ; 
 scalar_t__ TV_STD_PAL_M ; 
 scalar_t__* hor_timing_NTSC ; 
 scalar_t__* hor_timing_PAL ; 
 struct radeon_tv_mode_constants* radeon_legacy_tv_get_std_mode (struct radeon_encoder*,int /*<<< orphan*/ *) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static bool radeon_legacy_tv_init_restarts(struct drm_encoder *encoder)
{
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_tv_dac *tv_dac = radeon_encoder->enc_priv;
	int restart;
	unsigned int h_total, v_total, f_total;
	int v_offset, h_offset;
	u16 p1, p2, h_inc;
	bool h_changed;
	const struct radeon_tv_mode_constants *const_ptr;

	const_ptr = radeon_legacy_tv_get_std_mode(radeon_encoder, NULL);
	if (!const_ptr)
		return false;

	h_total = const_ptr->hor_total;
	v_total = const_ptr->ver_total;

	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60)
		f_total = NTSC_TV_VFTOTAL + 1;
	else
		f_total = PAL_TV_VFTOTAL + 1;

	/* adjust positions 1&2 in hor. cod timing table */
	h_offset = tv_dac->h_pos * H_POS_UNIT;

	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M) {
		h_offset -= 50;
		p1 = hor_timing_NTSC[H_TABLE_POS1];
		p2 = hor_timing_NTSC[H_TABLE_POS2];
	} else {
		p1 = hor_timing_PAL[H_TABLE_POS1];
		p2 = hor_timing_PAL[H_TABLE_POS2];
	}

	p1 = (u16)((int)p1 + h_offset);
	p2 = (u16)((int)p2 - h_offset);

	h_changed = (p1 != tv_dac->tv.h_code_timing[H_TABLE_POS1] ||
		     p2 != tv_dac->tv.h_code_timing[H_TABLE_POS2]);

	tv_dac->tv.h_code_timing[H_TABLE_POS1] = p1;
	tv_dac->tv.h_code_timing[H_TABLE_POS2] = p2;

	/* Convert hOffset from n. of TV clock periods to n. of CRTC clock periods (CRTC pixels) */
	h_offset = (h_offset * (int)(const_ptr->pix_to_tv)) / 1000;

	/* adjust restart */
	restart = const_ptr->def_restart;

	/*
	 * convert v_pos TV lines to n. of CRTC pixels
	 */
	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60)
		v_offset = ((int)(v_total * h_total) * 2 * tv_dac->v_pos) / (int)(NTSC_TV_LINES_PER_FRAME);
	else
		v_offset = ((int)(v_total * h_total) * 2 * tv_dac->v_pos) / (int)(PAL_TV_LINES_PER_FRAME);

	restart -= v_offset + h_offset;

	DRM_DEBUG_KMS("compute_restarts: def = %u h = %d v = %d, p1 = %04x, p2 = %04x, restart = %d\n",
		  const_ptr->def_restart, tv_dac->h_pos, tv_dac->v_pos, p1, p2, restart);

	tv_dac->tv.hrestart = restart % h_total;
	restart /= h_total;
	tv_dac->tv.vrestart = restart % v_total;
	restart /= v_total;
	tv_dac->tv.frestart = restart % f_total;

	DRM_DEBUG_KMS("compute_restart: F/H/V=%u,%u,%u\n",
		  (unsigned)tv_dac->tv.frestart,
		  (unsigned)tv_dac->tv.vrestart,
		  (unsigned)tv_dac->tv.hrestart);

	/* compute h_inc from hsize */
	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M)
		h_inc = (u16)((int)(const_ptr->hor_resolution * 4096 * NTSC_TV_CLOCK_T) /
			      (tv_dac->h_size * (int)(NTSC_TV_H_SIZE_UNIT) + (int)(NTSC_TV_ZERO_H_SIZE)));
	else
		h_inc = (u16)((int)(const_ptr->hor_resolution * 4096 * PAL_TV_CLOCK_T) /
			      (tv_dac->h_size * (int)(PAL_TV_H_SIZE_UNIT) + (int)(PAL_TV_ZERO_H_SIZE)));

	tv_dac->tv.timing_cntl = (tv_dac->tv.timing_cntl & ~RADEON_H_INC_MASK) |
		((u32)h_inc << RADEON_H_INC_SHIFT);

	DRM_DEBUG_KMS("compute_restart: h_size = %d h_inc = %d\n", tv_dac->h_size, h_inc);

	return h_changed;
}