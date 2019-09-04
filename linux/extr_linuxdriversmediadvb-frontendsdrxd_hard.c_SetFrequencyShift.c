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
typedef  scalar_t__ u32 ;
struct drxd_state {int tuner_mirrors; int fe_fs_add_incr; int org_fe_fs_add_incr; int /*<<< orphan*/  sys_clock_freq; scalar_t__ intermediate_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_FS_REG_ADD_INC_LOP__A ; 
 void* MulDiv32 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int Write32 (struct drxd_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SetFrequencyShift(struct drxd_state *state,
			     u32 offsetFreq, int channelMirrored)
{
	int negativeShift = (state->tuner_mirrors == channelMirrored);

	/* Handle all mirroring
	 *
	 * Note: ADC mirroring (aliasing) is implictly handled by limiting
	 * feFsRegAddInc to 28 bits below
	 * (if the result before masking is more than 28 bits, this means
	 *  that the ADC is mirroring.
	 * The masking is in fact the aliasing of the ADC)
	 *
	 */

	/* Compute register value, unsigned computation */
	state->fe_fs_add_incr = MulDiv32(state->intermediate_freq +
					 offsetFreq,
					 1 << 28, state->sys_clock_freq);
	/* Remove integer part */
	state->fe_fs_add_incr &= 0x0FFFFFFFL;
	if (negativeShift)
		state->fe_fs_add_incr = ((1 << 28) - state->fe_fs_add_incr);

	/* Save the frequency shift without tunerOffset compensation
	   for CtrlGetChannel. */
	state->org_fe_fs_add_incr = MulDiv32(state->intermediate_freq,
					     1 << 28, state->sys_clock_freq);
	/* Remove integer part */
	state->org_fe_fs_add_incr &= 0x0FFFFFFFL;
	if (negativeShift)
		state->org_fe_fs_add_incr = ((1L << 28) -
					     state->org_fe_fs_add_incr);

	return Write32(state, FE_FS_REG_ADD_INC_LOP__A,
		       state->fe_fs_add_incr, 0);
}