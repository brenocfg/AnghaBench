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
struct pvr2_hdw {scalar_t__ fw1_state; scalar_t__ flag_modulefail; scalar_t__ flag_init_ok; } ;

/* Variables and functions */
 scalar_t__ FW1_STATE_MISSING ; 
 scalar_t__ FW1_STATE_RELOAD ; 
 scalar_t__ FW1_STATE_UNKNOWN ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  PVR2_TRACE_INFO ; 
 int /*<<< orphan*/  PVR2_TRACE_INIT ; 
 scalar_t__ procreload ; 
 scalar_t__ pvr2_hdw_dev_ok (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_hdw_setup_low (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pvr2_upload_firmware1 (struct pvr2_hdw*) ; 

__attribute__((used)) static void pvr2_hdw_setup(struct pvr2_hdw *hdw)
{
	pvr2_trace(PVR2_TRACE_INIT,"pvr2_hdw_setup(hdw=%p) begin",hdw);
	do {
		pvr2_hdw_setup_low(hdw);
		pvr2_trace(PVR2_TRACE_INIT,
			   "pvr2_hdw_setup(hdw=%p) done, ok=%d init_ok=%d",
			   hdw,pvr2_hdw_dev_ok(hdw),hdw->flag_init_ok);
		if (pvr2_hdw_dev_ok(hdw)) {
			if (hdw->flag_init_ok) {
				pvr2_trace(
					PVR2_TRACE_INFO,
					"Device initialization completed successfully.");
				break;
			}
			if (hdw->fw1_state == FW1_STATE_RELOAD) {
				pvr2_trace(
					PVR2_TRACE_INFO,
					"Device microcontroller firmware (re)loaded; it should now reset and reconnect.");
				break;
			}
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Device initialization was not successful.");
			if (hdw->fw1_state == FW1_STATE_MISSING) {
				pvr2_trace(
					PVR2_TRACE_ERROR_LEGS,
					"Giving up since device microcontroller firmware appears to be missing.");
				break;
			}
		}
		if (hdw->flag_modulefail) {
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"***WARNING*** pvrusb2 driver initialization failed due to the failure of one or more sub-device kernel modules.");
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"You need to resolve the failing condition before this driver can function.  There should be some earlier messages giving more information about the problem.");
			break;
		}
		if (procreload) {
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Attempting pvrusb2 recovery by reloading primary firmware.");
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"If this works, device should disconnect and reconnect in a sane state.");
			hdw->fw1_state = FW1_STATE_UNKNOWN;
			pvr2_upload_firmware1(hdw);
		} else {
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"***WARNING*** pvrusb2 device hardware appears to be jammed and I can't clear it.");
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"You might need to power cycle the pvrusb2 device in order to recover.");
		}
	} while (0);
	pvr2_trace(PVR2_TRACE_INIT,"pvr2_hdw_setup(hdw=%p) end",hdw);
}