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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;
struct dc_crtc_timing {int pix_clk_khz; unsigned long long h_total; scalar_t__ v_total; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_VERTICAL_INTERRUPT0_LINE_END ; 
 int /*<<< orphan*/  OTG_VERTICAL_INTERRUPT0_LINE_START ; 
 int /*<<< orphan*/  OTG_VERTICAL_INTERRUPT0_POSITION ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long long div64_u64 (unsigned long long,int) ; 
 scalar_t__ get_start_vline (struct timing_generator*,struct dc_crtc_timing const*) ; 

void optc1_program_vline_interrupt(
		struct timing_generator *optc,
		const struct dc_crtc_timing *dc_crtc_timing,
		unsigned long long vsync_delta)
{

	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	unsigned long long req_delta_tens_of_usec = div64_u64((vsync_delta + 9999), 10000);
	unsigned long long pix_clk_hundreds_khz = div64_u64((dc_crtc_timing->pix_clk_khz + 99), 100);
	uint32_t req_delta_lines = (uint32_t) div64_u64(
			(req_delta_tens_of_usec * pix_clk_hundreds_khz + dc_crtc_timing->h_total - 1),
								dc_crtc_timing->h_total);

	uint32_t vsync_line = get_start_vline(optc, dc_crtc_timing);
	uint32_t start_line = 0;
	uint32_t endLine = 0;

	if (req_delta_lines != 0)
		req_delta_lines--;

	if (req_delta_lines > vsync_line)
		start_line = dc_crtc_timing->v_total - (req_delta_lines - vsync_line) - 1;
	else
		start_line = vsync_line - req_delta_lines;

	endLine = start_line + 2;

	if (endLine >= dc_crtc_timing->v_total)
		endLine = 2;

	REG_SET_2(OTG_VERTICAL_INTERRUPT0_POSITION, 0,
			OTG_VERTICAL_INTERRUPT0_LINE_START, start_line,
			OTG_VERTICAL_INTERRUPT0_LINE_END, endLine);
}