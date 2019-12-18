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

/* Variables and functions */
 int /*<<< orphan*/  SIGNAL_TYPE_NONE ; 
 int dce120_timing_generator_validate_timing (struct timing_generator*,struct dc_crtc_timing const*,int /*<<< orphan*/ ) ; 

bool dce120_tg_validate_timing(struct timing_generator *tg,
	const struct dc_crtc_timing *timing)
{
	return dce120_timing_generator_validate_timing(tg, timing, SIGNAL_TYPE_NONE);
}