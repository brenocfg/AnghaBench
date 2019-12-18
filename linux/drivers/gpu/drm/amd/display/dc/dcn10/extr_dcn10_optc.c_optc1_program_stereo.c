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
struct dc_crtc_timing {int dummy; } ;
struct crtc_stereo_flags {scalar_t__ PROGRAM_STEREO; } ;

/* Variables and functions */
 int /*<<< orphan*/  optc1_disable_stereo (struct timing_generator*) ; 
 int /*<<< orphan*/  optc1_enable_stereo (struct timing_generator*,struct dc_crtc_timing const*,struct crtc_stereo_flags*) ; 

void optc1_program_stereo(struct timing_generator *optc,
	const struct dc_crtc_timing *timing, struct crtc_stereo_flags *flags)
{
	if (flags->PROGRAM_STEREO)
		optc1_enable_stereo(optc, timing, flags);
	else
		optc1_disable_stereo(optc);
}