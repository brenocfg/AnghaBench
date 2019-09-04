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
struct awg_timing {int trailing_pixels; long blanking_level; scalar_t__ blanking_pixels; int active_pixels; } ;
struct awg_code_generation_params {int dummy; } ;

/* Variables and functions */
 int AWG_DELAY ; 
 int /*<<< orphan*/  RPLSET ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  SKIP ; 
 int awg_generate_instr (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int,struct awg_code_generation_params*) ; 

__attribute__((used)) static int awg_generate_line_signal(
		struct awg_code_generation_params *fwparams,
		struct awg_timing *timing)
{
	long int val;
	int ret = 0;

	if (timing->trailing_pixels > 0) {
		/* skip trailing pixel */
		val = timing->blanking_level;
		ret |= awg_generate_instr(RPLSET, val, 0, 0, fwparams);

		val = timing->trailing_pixels - 1 + AWG_DELAY;
		ret |= awg_generate_instr(SKIP, val, 0, 0, fwparams);
	}

	/* set DE signal high */
	val = timing->blanking_level;
	ret |= awg_generate_instr((timing->trailing_pixels > 0) ? SET : RPLSET,
			val, 0, 1, fwparams);

	if (timing->blanking_pixels > 0) {
		/* skip the number of active pixel */
		val = timing->active_pixels - 1;
		ret |= awg_generate_instr(SKIP, val, 0, 1, fwparams);

		/* set DE signal low */
		val = timing->blanking_level;
		ret |= awg_generate_instr(SET, val, 0, 0, fwparams);
	}

	return ret;
}