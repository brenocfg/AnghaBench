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
typedef  scalar_t__ uint32_t ;
struct plane_size {scalar_t__ chroma_pitch; scalar_t__ surface_pitch; } ;
struct hubp {int dummy; } ;
struct dcn20_hubp {int dummy; } ;
struct dc_plane_dcc_param {scalar_t__ meta_pitch; scalar_t__ meta_pitch_c; int /*<<< orphan*/  enable; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DCSURF_SURFACE_PITCH ; 
 int /*<<< orphan*/  DCSURF_SURFACE_PITCH_C ; 
 int /*<<< orphan*/  META_PITCH ; 
 int /*<<< orphan*/  META_PITCH_C ; 
 int /*<<< orphan*/  PITCH ; 
 int /*<<< orphan*/  PITCH_C ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int SURFACE_PIXEL_FORMAT_SUBSAMPLE_END ; 
 int SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 
 struct dcn20_hubp* TO_DCN20_HUBP (struct hubp*) ; 

void hubp2_program_size(
	struct hubp *hubp,
	enum surface_pixel_format format,
	const struct plane_size *plane_size,
	struct dc_plane_dcc_param *dcc)
{
	struct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t pitch, meta_pitch, pitch_c, meta_pitch_c;
	bool use_pitch_c = false;

	/* Program data and meta surface pitch (calculation from addrlib)
	 * 444 or 420 luma
	 */
	use_pitch_c = format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN
		&& format < SURFACE_PIXEL_FORMAT_SUBSAMPLE_END;
	if (use_pitch_c) {
		ASSERT(plane_size->chroma_pitch != 0);
		/* Chroma pitch zero can cause system hang! */

		pitch = plane_size->surface_pitch - 1;
		meta_pitch = dcc->meta_pitch - 1;
		pitch_c = plane_size->chroma_pitch - 1;
		meta_pitch_c = dcc->meta_pitch_c - 1;
	} else {
		pitch = plane_size->surface_pitch - 1;
		meta_pitch = dcc->meta_pitch - 1;
		pitch_c = 0;
		meta_pitch_c = 0;
	}

	if (!dcc->enable) {
		meta_pitch = 0;
		meta_pitch_c = 0;
	}

	REG_UPDATE_2(DCSURF_SURFACE_PITCH,
			PITCH, pitch, META_PITCH, meta_pitch);

	use_pitch_c = format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN;
	if (use_pitch_c)
		REG_UPDATE_2(DCSURF_SURFACE_PITCH_C,
			PITCH_C, pitch_c, META_PITCH_C, meta_pitch_c);
}