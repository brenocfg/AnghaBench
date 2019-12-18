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
struct pqi_ctrl_info {int pqi_mode_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQI_PENDING_IO_TIMEOUT_SECS ; 
 int /*<<< orphan*/  SIS_MODE ; 
 int /*<<< orphan*/  pqi_cancel_rescan_worker (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_cancel_update_time_worker (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_block_requests (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_ofa_start (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_wait_for_pending_io (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_ctrl_wait_until_quiesced (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_fail_io_queued_for_all_devices (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_save_ctrl_mode (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_stop_heartbeat_timer (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_wait_until_inbound_queues_empty (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_wait_until_lun_reset_finished (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_wait_until_scan_finished (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_ofa_ctrl_quiesce(struct pqi_ctrl_info *ctrl_info)
{
	pqi_cancel_update_time_worker(ctrl_info);
	pqi_cancel_rescan_worker(ctrl_info);
	pqi_wait_until_lun_reset_finished(ctrl_info);
	pqi_wait_until_scan_finished(ctrl_info);
	pqi_ctrl_ofa_start(ctrl_info);
	pqi_ctrl_block_requests(ctrl_info);
	pqi_ctrl_wait_until_quiesced(ctrl_info);
	pqi_ctrl_wait_for_pending_io(ctrl_info, PQI_PENDING_IO_TIMEOUT_SECS);
	pqi_fail_io_queued_for_all_devices(ctrl_info);
	pqi_wait_until_inbound_queues_empty(ctrl_info);
	pqi_stop_heartbeat_timer(ctrl_info);
	ctrl_info->pqi_mode_enabled = false;
	pqi_save_ctrl_mode(ctrl_info, SIS_MODE);
}