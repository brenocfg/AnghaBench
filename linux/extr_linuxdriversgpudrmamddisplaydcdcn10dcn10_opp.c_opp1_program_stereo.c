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
struct output_pixel_processor {int dummy; } ;
struct dcn10_opp {int dummy; } ;
struct dc_crtc_timing {scalar_t__ timing_3d_format; scalar_t__ v_addressable; scalar_t__ v_total; scalar_t__ h_border_right; scalar_t__ h_addressable; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_CONTROL ; 
 int /*<<< orphan*/  FMT_STEREOSYNC_OVERRIDE ; 
 int /*<<< orphan*/  OPPBUF_3D_PARAMETERS_0 ; 
 int /*<<< orphan*/  OPPBUF_3D_VACT_SPACE1_SIZE ; 
 int /*<<< orphan*/  OPPBUF_3D_VACT_SPACE2_SIZE ; 
 int /*<<< orphan*/  OPPBUF_ACTIVE_WIDTH ; 
 int /*<<< orphan*/  OPPBUF_CONTROL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TIMING_3D_FORMAT_FRAME_ALTERNATE ; 
 struct dcn10_opp* TO_DCN10_OPP (struct output_pixel_processor*) ; 

void opp1_program_stereo(
	struct output_pixel_processor *opp,
	bool enable,
	const struct dc_crtc_timing *timing)
{
	struct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	uint32_t active_width = timing->h_addressable - timing->h_border_right - timing->h_border_right;
	uint32_t space1_size = timing->v_total - timing->v_addressable;
	/* TODO: confirm computation of space2_size */
	uint32_t space2_size = timing->v_total - timing->v_addressable;

	if (!enable) {
		active_width = 0;
		space1_size = 0;
		space2_size = 0;
	}

	/* TODO: for which cases should FMT_STEREOSYNC_OVERRIDE be set? */
	REG_UPDATE(FMT_CONTROL, FMT_STEREOSYNC_OVERRIDE, 0);

	REG_UPDATE(OPPBUF_CONTROL, OPPBUF_ACTIVE_WIDTH, active_width);

	/* Program OPPBUF_3D_VACT_SPACE1_SIZE and OPPBUF_VACT_SPACE2_SIZE registers
	 * In 3D progressive frames, Vactive space happens only in between the 2 frames,
	 * so only need to program OPPBUF_3D_VACT_SPACE1_SIZE
	 * In 3D alternative frames, left and right frames, top and bottom field.
	 */
	if (timing->timing_3d_format == TIMING_3D_FORMAT_FRAME_ALTERNATE)
		REG_UPDATE(OPPBUF_3D_PARAMETERS_0, OPPBUF_3D_VACT_SPACE2_SIZE, space2_size);
	else
		REG_UPDATE(OPPBUF_3D_PARAMETERS_0, OPPBUF_3D_VACT_SPACE1_SIZE, space1_size);

	/* TODO: Is programming of OPPBUF_DUMMY_DATA_R/G/B needed? */
	/*
	REG_UPDATE(OPPBUF_3D_PARAMETERS_0,
			OPPBUF_DUMMY_DATA_R, data_r);
	REG_UPDATE(OPPBUF_3D_PARAMETERS_1,
			OPPBUF_DUMMY_DATA_G, data_g);
	REG_UPDATE(OPPBUF_3D_PARAMETERS_1,
			OPPBUF_DUMMY_DATA_B, _data_b);
	*/
}