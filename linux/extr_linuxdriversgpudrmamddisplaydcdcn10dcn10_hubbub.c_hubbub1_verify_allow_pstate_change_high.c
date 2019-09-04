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
struct hubbub {int /*<<< orphan*/  debug_test_index_pstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_ENABLE ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_VALUE ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DRAM_STATE_CNTL ; 
 int /*<<< orphan*/  DCHUBBUB_TEST_DEBUG_DATA ; 
 int /*<<< orphan*/  DCHUBBUB_TEST_DEBUG_INDEX ; 
 int /*<<< orphan*/  DC_LOG_WARNING (char*,unsigned int) ; 
 unsigned int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool hubbub1_verify_allow_pstate_change_high(
	struct hubbub *hubbub)
{
	/* pstate latency is ~20us so if we wait over 40us and pstate allow
	 * still not asserted, we are probably stuck and going to hang
	 *
	 * TODO: Figure out why it takes ~100us on linux
	 * pstate takes around ~100us on linux. Unknown currently as to
	 * why it takes that long on linux
	 */
	static unsigned int pstate_wait_timeout_us = 200;
	static unsigned int pstate_wait_expected_timeout_us = 40;
	static unsigned int max_sampled_pstate_wait_us; /* data collection */
	static bool forced_pstate_allow; /* help with revert wa */

	unsigned int debug_data;
	unsigned int i;

	if (forced_pstate_allow) {
		/* we hacked to force pstate allow to prevent hang last time
		 * we verify_allow_pstate_change_high.  so disable force
		 * here so we can check status
		 */
		REG_UPDATE_2(DCHUBBUB_ARB_DRAM_STATE_CNTL,
			     DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_VALUE, 0,
			     DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_ENABLE, 0);
		forced_pstate_allow = false;
	}

	/* RV1:
	 * dchubbubdebugind, at: 0x7
	 * description "3-0:   Pipe0 cursor0 QOS
	 * 7-4:   Pipe1 cursor0 QOS
	 * 11-8:  Pipe2 cursor0 QOS
	 * 15-12: Pipe3 cursor0 QOS
	 * 16:    Pipe0 Plane0 Allow Pstate Change
	 * 17:    Pipe1 Plane0 Allow Pstate Change
	 * 18:    Pipe2 Plane0 Allow Pstate Change
	 * 19:    Pipe3 Plane0 Allow Pstate Change
	 * 20:    Pipe0 Plane1 Allow Pstate Change
	 * 21:    Pipe1 Plane1 Allow Pstate Change
	 * 22:    Pipe2 Plane1 Allow Pstate Change
	 * 23:    Pipe3 Plane1 Allow Pstate Change
	 * 24:    Pipe0 cursor0 Allow Pstate Change
	 * 25:    Pipe1 cursor0 Allow Pstate Change
	 * 26:    Pipe2 cursor0 Allow Pstate Change
	 * 27:    Pipe3 cursor0 Allow Pstate Change
	 * 28:    WB0 Allow Pstate Change
	 * 29:    WB1 Allow Pstate Change
	 * 30:    Arbiter's allow_pstate_change
	 * 31:    SOC pstate change request
	 */


	REG_WRITE(DCHUBBUB_TEST_DEBUG_INDEX, hubbub->debug_test_index_pstate);

	for (i = 0; i < pstate_wait_timeout_us; i++) {
		debug_data = REG_READ(DCHUBBUB_TEST_DEBUG_DATA);

		if (debug_data & (1 << 30)) {

			if (i > pstate_wait_expected_timeout_us)
				DC_LOG_WARNING("pstate took longer than expected ~%dus\n",
						i);

			return true;
		}
		if (max_sampled_pstate_wait_us < i)
			max_sampled_pstate_wait_us = i;

		udelay(1);
	}

	/* force pstate allow to prevent system hang
	 * and break to debugger to investigate
	 */
	REG_UPDATE_2(DCHUBBUB_ARB_DRAM_STATE_CNTL,
		     DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_VALUE, 1,
		     DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_ENABLE, 1);
	forced_pstate_allow = true;

	DC_LOG_WARNING("pstate TEST_DEBUG_DATA: 0x%X\n",
			debug_data);

	return false;
}