#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int fw_heartbeat_counter; int seconds_since_last_heartbeat; int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_PEG_ALIVE_COUNTER ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_timer ; 
 int qla82xx_rd_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla82xx_check_fw_alive(scsi_qla_host_t *vha)
{
	uint32_t fw_heartbeat_counter;
	int status = 0;

	fw_heartbeat_counter = qla82xx_rd_32(vha->hw,
		QLA82XX_PEG_ALIVE_COUNTER);
	/* all 0xff, assume AER/EEH in progress, ignore */
	if (fw_heartbeat_counter == 0xffffffff) {
		ql_dbg(ql_dbg_timer, vha, 0x6003,
		    "FW heartbeat counter is 0xffffffff, "
		    "returning status=%d.\n", status);
		return status;
	}
	if (vha->fw_heartbeat_counter == fw_heartbeat_counter) {
		vha->seconds_since_last_heartbeat++;
		/* FW not alive after 2 seconds */
		if (vha->seconds_since_last_heartbeat == 2) {
			vha->seconds_since_last_heartbeat = 0;
			status = 1;
		}
	} else
		vha->seconds_since_last_heartbeat = 0;
	vha->fw_heartbeat_counter = fw_heartbeat_counter;
	if (status)
		ql_dbg(ql_dbg_timer, vha, 0x6004,
		    "Returning status=%d.\n", status);
	return status;
}