#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  void* u16 ;
typedef  scalar_t__ sysClockFreq ;
struct TYPE_4__ {int /*<<< orphan*/  (* osc_deviation ) (int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_3__ {int bandwidth_hz; } ;
struct drxd_state {int osc_clock_deviation; int /*<<< orphan*/  cscd_state; int /*<<< orphan*/  current_fe_if_incr; int /*<<< orphan*/  priv; TYPE_2__ config; void* sys_clock_freq; scalar_t__ expected_sys_clock_freq; TYPE_1__ props; scalar_t__ type_A; } ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  CSCD_SAVED ; 
 int DRXD_BANDWIDTH_6MHZ_IN_HZ ; 
 int DRXD_BANDWIDTH_7MHZ_IN_HZ ; 
 int DRXD_BANDWIDTH_8MHZ_IN_HZ ; 
 int /*<<< orphan*/  DRXD_OSCDEV_DONT_SCAN ; 
 int /*<<< orphan*/  FE_IF_REG_INCR0__A ; 
 int /*<<< orphan*/  LC_RA_RAM_IFINCR_NOM_L__A ; 
 int MulDiv32 (int,int,int) ; 
 int Read32 (struct drxd_state*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_RA_RAM_IF_SAVE__AX ; 
 int /*<<< orphan*/  SC_RA_RAM_SAMPLE_RATE_COUNT__A ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int CorrectSysClockDeviation(struct drxd_state *state)
{
	int status;
	s32 incr = 0;
	s32 nomincr = 0;
	u32 bandwidth = 0;
	u32 sysClockInHz = 0;
	u32 sysClockFreq = 0;	/* in kHz */
	s16 oscClockDeviation;
	s16 Diff;

	do {
		/* Retrieve bandwidth and incr, sanity check */

		/* These accesses should be AtomicReadReg32, but that
		   causes trouble (at least for diversity */
		status = Read32(state, LC_RA_RAM_IFINCR_NOM_L__A, ((u32 *) &nomincr), 0);
		if (status < 0)
			break;
		status = Read32(state, FE_IF_REG_INCR0__A, (u32 *) &incr, 0);
		if (status < 0)
			break;

		if (state->type_A) {
			if ((nomincr - incr < -500) || (nomincr - incr > 500))
				break;
		} else {
			if ((nomincr - incr < -2000) || (nomincr - incr > 2000))
				break;
		}

		switch (state->props.bandwidth_hz) {
		case 8000000:
			bandwidth = DRXD_BANDWIDTH_8MHZ_IN_HZ;
			break;
		case 7000000:
			bandwidth = DRXD_BANDWIDTH_7MHZ_IN_HZ;
			break;
		case 6000000:
			bandwidth = DRXD_BANDWIDTH_6MHZ_IN_HZ;
			break;
		default:
			return -1;
			break;
		}

		/* Compute new sysclock value
		   sysClockFreq = (((incr + 2^23)*bandwidth)/2^21)/1000 */
		incr += (1 << 23);
		sysClockInHz = MulDiv32(incr, bandwidth, 1 << 21);
		sysClockFreq = (u32) (sysClockInHz / 1000);
		/* rounding */
		if ((sysClockInHz % 1000) > 500)
			sysClockFreq++;

		/* Compute clock deviation in ppm */
		oscClockDeviation = (u16) ((((s32) (sysClockFreq) -
					     (s32)
					     (state->expected_sys_clock_freq)) *
					    1000000L) /
					   (s32)
					   (state->expected_sys_clock_freq));

		Diff = oscClockDeviation - state->osc_clock_deviation;
		/*printk(KERN_INFO "sysclockdiff=%d\n", Diff); */
		if (Diff >= -200 && Diff <= 200) {
			state->sys_clock_freq = (u16) sysClockFreq;
			if (oscClockDeviation != state->osc_clock_deviation) {
				if (state->config.osc_deviation) {
					state->config.osc_deviation(state->priv,
								    oscClockDeviation,
								    1);
					state->osc_clock_deviation =
					    oscClockDeviation;
				}
			}
			/* switch OFF SRMM scan in SC */
			status = Write16(state, SC_RA_RAM_SAMPLE_RATE_COUNT__A, DRXD_OSCDEV_DONT_SCAN, 0);
			if (status < 0)
				break;
			/* overrule FE_IF internal value for
			   proper re-locking */
			status = Write16(state, SC_RA_RAM_IF_SAVE__AX, state->current_fe_if_incr, 0);
			if (status < 0)
				break;
			state->cscd_state = CSCD_SAVED;
		}
	} while (0);

	return status;
}