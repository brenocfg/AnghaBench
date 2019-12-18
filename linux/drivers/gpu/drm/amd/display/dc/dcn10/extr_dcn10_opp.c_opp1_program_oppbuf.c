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
struct output_pixel_processor {int dummy; } ;
struct oppbuf_params {int /*<<< orphan*/  num_segment_padded_pixels; int /*<<< orphan*/  pixel_repetition; int /*<<< orphan*/  mso_overlap_pixel_num; int /*<<< orphan*/  mso_segmentation; int /*<<< orphan*/  active_width; } ;
struct dcn10_opp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPPBUF_ACTIVE_WIDTH ; 
 int /*<<< orphan*/  OPPBUF_CONTROL ; 
 int /*<<< orphan*/  OPPBUF_CONTROL1 ; 
 int /*<<< orphan*/  OPPBUF_DISPLAY_SEGMENTATION ; 
 int /*<<< orphan*/  OPPBUF_NUM_SEGMENT_PADDED_PIXELS ; 
 int /*<<< orphan*/  OPPBUF_OVERLAP_PIXEL_NUM ; 
 int /*<<< orphan*/  OPPBUF_PIXEL_REPETITION ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_opp* TO_DCN10_OPP (struct output_pixel_processor*) ; 

void opp1_program_oppbuf(
	struct output_pixel_processor *opp,
	struct oppbuf_params *oppbuf)
{
	struct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	/* Program the oppbuf active width to be the frame width from mpc */
	REG_UPDATE(OPPBUF_CONTROL, OPPBUF_ACTIVE_WIDTH, oppbuf->active_width);

	/* Specifies the number of segments in multi-segment mode (DP-MSO operation)
	 * description  "In 1/2/4 segment mode, specifies the horizontal active width in pixels of the display panel.
	 * In 4 segment split left/right mode, specifies the horizontal 1/2 active width in pixels of the display panel.
	 * Used to determine segment boundaries in multi-segment mode. Used to determine the width of the vertical active space in 3D frame packed modes.
	 * OPPBUF_ACTIVE_WIDTH must be integer divisible by the total number of segments."
	 */
	REG_UPDATE(OPPBUF_CONTROL, OPPBUF_DISPLAY_SEGMENTATION, oppbuf->mso_segmentation);

	/* description  "Specifies the number of overlap pixels (1-8 overlapping pixels supported), used in multi-segment mode (DP-MSO operation)" */
	REG_UPDATE(OPPBUF_CONTROL, OPPBUF_OVERLAP_PIXEL_NUM, oppbuf->mso_overlap_pixel_num);

	/* description  "Specifies the number of times a pixel is replicated (0-15 pixel replications supported).
	 * A value of 0 disables replication. The total number of times a pixel is output is OPPBUF_PIXEL_REPETITION + 1."
	 */
	REG_UPDATE(OPPBUF_CONTROL, OPPBUF_PIXEL_REPETITION, oppbuf->pixel_repetition);

#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	/* Controls the number of padded pixels at the end of a segment */
	if (REG(OPPBUF_CONTROL1))
		REG_UPDATE(OPPBUF_CONTROL1, OPPBUF_NUM_SEGMENT_PADDED_PIXELS, oppbuf->num_segment_padded_pixels);
#endif
}