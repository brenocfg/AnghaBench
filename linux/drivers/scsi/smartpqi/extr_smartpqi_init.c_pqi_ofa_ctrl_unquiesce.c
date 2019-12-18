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
struct pqi_ctrl_info {int pqi_mode_enabled; int controller_online; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQI_MODE ; 
 int /*<<< orphan*/  PQI_SOFT_RESET_ABORT ; 
 int /*<<< orphan*/  pqi_clear_soft_reset_status (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_ctrl_unblock_requests (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ofa_free_host_buffer (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_save_ctrl_mode (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_scan_scsi_devices (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_schedule_update_time_worker (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_start_heartbeat_timer (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_ofa_ctrl_unquiesce(struct pqi_ctrl_info *ctrl_info)
{
	pqi_ofa_free_host_buffer(ctrl_info);
	ctrl_info->pqi_mode_enabled = true;
	pqi_save_ctrl_mode(ctrl_info, PQI_MODE);
	ctrl_info->controller_online = true;
	pqi_ctrl_unblock_requests(ctrl_info);
	pqi_start_heartbeat_timer(ctrl_info);
	pqi_schedule_update_time_worker(ctrl_info);
	pqi_clear_soft_reset_status(ctrl_info,
		PQI_SOFT_RESET_ABORT);
	pqi_scan_scsi_devices(ctrl_info);
}