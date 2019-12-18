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
struct dcn10_opp {int dummy; } ;
struct clamping_and_pixel_encoding_params {scalar_t__ pixel_encoding; } ;
struct bit_depth_reduction_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_MAP420MEM_PWR_FORCE ; 
 int /*<<< orphan*/  FMT_MAP420_MEMORY_CONTROL ; 
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_opp* TO_DCN10_OPP (struct output_pixel_processor*) ; 
 int /*<<< orphan*/  opp1_program_bit_depth_reduction (struct output_pixel_processor*,struct bit_depth_reduction_params*) ; 
 int /*<<< orphan*/  opp1_program_clamping_and_pixel_encoding (struct output_pixel_processor*,struct clamping_and_pixel_encoding_params*) ; 

void opp1_program_fmt(
	struct output_pixel_processor *opp,
	struct bit_depth_reduction_params *fmt_bit_depth,
	struct clamping_and_pixel_encoding_params *clamping)
{
	struct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	if (clamping->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		REG_UPDATE(FMT_MAP420_MEMORY_CONTROL, FMT_MAP420MEM_PWR_FORCE, 0);

	/* dithering is affected by <CrtcSourceSelect>, hence should be
	 * programmed afterwards */
	opp1_program_bit_depth_reduction(
		opp,
		fmt_bit_depth);

	opp1_program_clamping_and_pixel_encoding(
		opp,
		clamping);

	return;
}