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
typedef  int uint32_t ;

/* Variables and functions */
 int DOWN_SCALE_RATIO_MAX ; 
 int EINVAL ; 
 int EOVERFLOW ; 
 int PHASE_STEP_SHIFT ; 
 int mult_frac (int,int,int) ; 

__attribute__((used)) static int calc_phase_step(uint32_t src, uint32_t dst, uint32_t *out_phase)
{
	uint32_t unit;

	if (src == 0 || dst == 0)
		return -EINVAL;

	/*
	 * PHASE_STEP_X/Y is coded on 26 bits (25:0),
	 * where 2^21 represents the unity "1" in fixed-point hardware design.
	 * This leaves 5 bits for the integer part (downscale case):
	 *	-> maximum downscale ratio = 0b1_1111 = 31
	 */
	if (src > (dst * DOWN_SCALE_RATIO_MAX))
		return -EOVERFLOW;

	unit = 1 << PHASE_STEP_SHIFT;
	*out_phase = mult_frac(unit, src, dst);

	return 0;
}