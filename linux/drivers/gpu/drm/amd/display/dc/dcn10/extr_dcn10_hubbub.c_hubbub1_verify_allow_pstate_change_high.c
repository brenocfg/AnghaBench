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
struct hubbub {int dummy; } ;
struct dcn10_hubbub {int /*<<< orphan*/  debug_test_index_pstate; } ;

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
 struct dcn10_hubbub* TO_DCN10_HUBBUB (struct hubbub*) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool hubbub1_verify_allow_pstate_change_high(
	struct hubbub *hubbub)
{
	struct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

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

	/* RV2:
	 * dchubbubdebugind, at: 0xB
	 * description
	 * 0:     Pipe0 Plane0 Allow Pstate Change
	 * 1:     Pipe0 Plane1 Allow Pstate Change
	 * 2:     Pipe0 Cursor0 Allow Pstate Change
	 * 3:     Pipe0 Cursor1 Allow Pstate Change
	 * 4:     Pipe1 Plane0 Allow Pstate Change
	 * 5:     Pipe1 Plane1 Allow Pstate Change
	 * 6:     Pipe1 Cursor0 Allow Pstate Change
	 * 7:     Pipe1 Cursor1 Allow Pstate Change
	 * 8:     Pipe2 Plane0 Allow Pstate Change
	 * 9:     Pipe2 Plane1 Allow Pstate Change
	 * 10:    Pipe2 Cursor0 Allow Pstate Change
	 * 11:    Pipe2 Cursor1 Allow Pstate Change
	 * 12:    Pipe3 Plane0 Allow Pstate Change
	 * 13:    Pipe3 Plane1 Allow Pstate Change
	 * 14:    Pipe3 Cursor0 Allow Pstate Change
	 * 15:    Pipe3 Cursor1 Allow Pstate Change
	 * 16:    Pipe4 Plane0 Allow Pstate Change
	 * 17:    Pipe4 Plane1 Allow Pstate Change
	 * 18:    Pipe4 Cursor0 Allow Pstate Change
	 * 19:    Pipe4 Cursor1 Allow Pstate Change
	 * 20:    Pipe5 Plane0 Allow Pstate Change
	 * 21:    Pipe5 Plane1 Allow Pstate Change
	 * 22:    Pipe5 Cursor0 Allow Pstate Change
	 * 23:    Pipe5 Cursor1 Allow Pstate Change
	 * 24:    Pipe6 Plane0 Allow Pstate Change
	 * 25:    Pipe6 Plane1 Allow Pstate Change
	 * 26:    Pipe6 Cursor0 Allow Pstate Change
	 * 27:    Pipe6 Cursor1 Allow Pstate Change
	 * 28:    WB0 Allow Pstate Change
	 * 29:    WB1 Allow Pstate Change
	 * 30:    Arbiter's allow_pstate_change
	 * 31:    SOC pstate change request"
	 */
	/*DCN2.x:
	HUBBUB:DCHUBBUB_TEST_ARB_DEBUG10 DCHUBBUBDEBUGIND:0xB
	0: Pipe0 Plane0 Allow P-state Change
	1: Pipe0 Plane1 Allow P-state Change
	2: Pipe0 Cursor0 Allow P-state Change
	3: Pipe0 Cursor1 Allow P-state Change
	4: Pipe1 Plane0 Allow P-state Change
	5: Pipe1 Plane1 Allow P-state Change
	6: Pipe1 Cursor0 Allow P-state Change
	7: Pipe1 Cursor1 Allow P-state Change
	8: Pipe2 Plane0 Allow P-state Change
	9: Pipe2 Plane1 Allow P-state Change
	10: Pipe2 Cursor0 Allow P-state Change
	11: Pipe2 Cursor1 Allow P-state Change
	12: Pipe3 Plane0 Allow P-state Change
	13: Pipe3 Plane1 Allow P-state Change
	14: Pipe3 Cursor0 Allow P-state Change
	15: Pipe3 Cursor1 Allow P-state Change
	16: Pipe4 Plane0 Allow P-state Change
	17: Pipe4 Plane1 Allow P-state Change
	18: Pipe4 Cursor0 Allow P-state Change
	19: Pipe4 Cursor1 Allow P-state Change
	20: Pipe5 Plane0 Allow P-state Change
	21: Pipe5 Plane1 Allow P-state Change
	22: Pipe5 Cursor0 Allow P-state Change
	23: Pipe5 Cursor1 Allow P-state Change
	24: Pipe6 Plane0 Allow P-state Change
	25: Pipe6 Plane1 Allow P-state Change
	26: Pipe6 Cursor0 Allow P-state Change
	27: Pipe6 Cursor1 Allow P-state Change
	28: WB0 Allow P-state Change
	29: WB1 Allow P-state Change
	30: Arbiter`s Allow P-state Change
	31: SOC P-state Change request
	*/
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

	REG_WRITE(DCHUBBUB_TEST_DEBUG_INDEX, hubbub1->debug_test_index_pstate);

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