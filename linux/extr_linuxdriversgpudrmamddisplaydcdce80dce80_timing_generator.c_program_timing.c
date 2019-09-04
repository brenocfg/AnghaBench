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
struct timing_generator {int dummy; } ;
struct dc_crtc_timing {int /*<<< orphan*/  pix_clk_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce110_tg_program_timing (struct timing_generator*,struct dc_crtc_timing const*,int) ; 
 int /*<<< orphan*/  program_pix_dur (struct timing_generator*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_timing(struct timing_generator *tg,
	const struct dc_crtc_timing *timing,
	bool use_vbios)
{
	if (!use_vbios)
		program_pix_dur(tg, timing->pix_clk_khz);

	dce110_tg_program_timing(tg, timing, use_vbios);
}