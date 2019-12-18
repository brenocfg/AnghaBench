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
typedef  int u32 ;
struct hfi1_pportdata {struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,...) ; 
 int /*<<< orphan*/  state_complete_reason_code_string (struct hfi1_pportdata*,int) ; 
 int /*<<< orphan*/  state_completed_string (int) ; 

__attribute__((used)) static void decode_state_complete(struct hfi1_pportdata *ppd, u32 frame,
				  const char *prefix)
{
	struct hfi1_devdata *dd = ppd->dd;
	u32 success;
	u32 state;
	u32 reason;
	u32 lanes;

	/*
	 * Decode frame:
	 *  [ 0: 0] - success
	 *  [ 3: 1] - state
	 *  [ 7: 4] - next state timeout
	 *  [15: 8] - reason code
	 *  [31:16] - lanes
	 */
	success = frame & 0x1;
	state = (frame >> 1) & 0x7;
	reason = (frame >> 8) & 0xff;
	lanes = (frame >> 16) & 0xffff;

	dd_dev_err(dd, "Last %s LNI state complete frame 0x%08x:\n",
		   prefix, frame);
	dd_dev_err(dd, "    last reported state state: %s (0x%x)\n",
		   state_completed_string(state), state);
	dd_dev_err(dd, "    state successfully completed: %s\n",
		   success ? "yes" : "no");
	dd_dev_err(dd, "    fail reason 0x%x: %s\n",
		   reason, state_complete_reason_code_string(ppd, reason));
	dd_dev_err(dd, "    passing lane mask: 0x%x", lanes);
}