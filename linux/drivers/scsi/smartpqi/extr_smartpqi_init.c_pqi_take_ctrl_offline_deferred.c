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
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pqi_cancel_rescan_worker (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_cancel_update_time_worker (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_clear_all_queued_raid_bypass_retries (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_unblock_requests (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_wait_until_quiesced (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_fail_all_outstanding_requests (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_free_interrupts (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_perform_lockup_action () ; 
 int /*<<< orphan*/  pqi_stop_heartbeat_timer (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_take_ctrl_offline_deferred(struct pqi_ctrl_info *ctrl_info)
{
	pqi_perform_lockup_action();
	pqi_stop_heartbeat_timer(ctrl_info);
	pqi_free_interrupts(ctrl_info);
	pqi_cancel_rescan_worker(ctrl_info);
	pqi_cancel_update_time_worker(ctrl_info);
	pqi_ctrl_wait_until_quiesced(ctrl_info);
	pqi_fail_all_outstanding_requests(ctrl_info);
	pqi_clear_all_queued_raid_bypass_retries(ctrl_info);
	pqi_ctrl_unblock_requests(ctrl_info);
}