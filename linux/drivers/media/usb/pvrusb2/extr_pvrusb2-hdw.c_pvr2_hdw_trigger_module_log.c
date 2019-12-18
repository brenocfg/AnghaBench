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
struct pvr2_hdw {int /*<<< orphan*/  big_lock; int /*<<< orphan*/  enc_ctl_state; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVR2_TRACE_INFO ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx2341x_log_status (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  log_status ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int pvr2_hdw_get_unit_number (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_hdw_state_log_state (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pvr2_hdw_trigger_module_log(struct pvr2_hdw *hdw)
{
	int nr = pvr2_hdw_get_unit_number(hdw);
	LOCK_TAKE(hdw->big_lock);
	do {
		pr_info("pvrusb2: =================  START STATUS CARD #%d  =================\n", nr);
		v4l2_device_call_all(&hdw->v4l2_dev, 0, core, log_status);
		pvr2_trace(PVR2_TRACE_INFO,"cx2341x config:");
		cx2341x_log_status(&hdw->enc_ctl_state, "pvrusb2");
		pvr2_hdw_state_log_state(hdw);
		pr_info("pvrusb2: ==================  END STATUS CARD #%d  ==================\n", nr);
	} while (0);
	LOCK_GIVE(hdw->big_lock);
}