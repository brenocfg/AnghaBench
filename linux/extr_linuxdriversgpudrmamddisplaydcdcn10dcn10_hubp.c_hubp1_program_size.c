#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ surface_pitch; } ;
struct TYPE_5__ {scalar_t__ chroma_pitch; scalar_t__ luma_pitch; } ;
union plane_size {TYPE_3__ grph; TYPE_1__ video; } ;
typedef  scalar_t__ uint32_t ;
struct hubp {int dummy; } ;
struct dcn10_hubp {int dummy; } ;
struct TYPE_8__ {scalar_t__ meta_pitch; } ;
struct TYPE_6__ {scalar_t__ meta_pitch_l; scalar_t__ meta_pitch_c; } ;
struct dc_plane_dcc_param {int /*<<< orphan*/  enable; TYPE_4__ grph; TYPE_2__ video; } ;
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
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 

void hubp1_program_size(
	struct hubp *hubp,
	enum surface_pixel_format format,
	const union plane_size *plane_size,
	struct dc_plane_dcc_param *dcc)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uint32_t pitch, meta_pitch, pitch_c, meta_pitch_c;

	/* Program data and meta surface pitch (calculation from addrlib)
	 * 444 or 420 luma
	 */
	if (format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN && format < SURFACE_PIXEL_FORMAT_SUBSAMPLE_END) {
		ASSERT(plane_size->video.chroma_pitch != 0);
		/* Chroma pitch zero can cause system hang! */

		pitch = plane_size->video.luma_pitch - 1;
		meta_pitch = dcc->video.meta_pitch_l - 1;
		pitch_c = plane_size->video.chroma_pitch - 1;
		meta_pitch_c = dcc->video.meta_pitch_c - 1;
	} else {
		pitch = plane_size->grph.surface_pitch - 1;
		meta_pitch = dcc->grph.meta_pitch - 1;
		pitch_c = 0;
		meta_pitch_c = 0;
	}

	if (!dcc->enable) {
		meta_pitch = 0;
		meta_pitch_c = 0;
	}

	REG_UPDATE_2(DCSURF_SURFACE_PITCH,
			PITCH, pitch, META_PITCH, meta_pitch);

	if (format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		REG_UPDATE_2(DCSURF_SURFACE_PITCH_C,
			PITCH_C, pitch_c, META_PITCH_C, meta_pitch_c);
}