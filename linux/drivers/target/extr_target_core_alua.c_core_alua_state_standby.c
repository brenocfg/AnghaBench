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
struct se_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCQ_04H_ALUA_TG_PT_STANDBY ; 
#define  INQUIRY 147 
#define  LOG_SELECT 146 
#define  LOG_SENSE 145 
#define  MAINTENANCE_IN 144 
#define  MAINTENANCE_OUT 143 
#define  MI_REPORT_TARGET_PGS 142 
#define  MODE_SELECT 141 
#define  MODE_SENSE 140 
#define  MO_SET_TARGET_PGS 139 
#define  PERSISTENT_RESERVE_IN 138 
#define  PERSISTENT_RESERVE_OUT 137 
#define  READ_BUFFER 136 
#define  READ_CAPACITY 135 
#define  RECEIVE_DIAGNOSTIC 134 
#define  REPORT_LUNS 133 
#define  REQUEST_SENSE 132 
#define  SAI_READ_CAPACITY_16 131 
#define  SEND_DIAGNOSTIC 130 
#define  SERVICE_ACTION_IN_16 129 
#define  WRITE_BUFFER 128 
 int /*<<< orphan*/  set_ascq (struct se_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int core_alua_state_standby(
	struct se_cmd *cmd,
	unsigned char *cdb)
{
	/*
	 * Allowed CDBs for ALUA_ACCESS_STATE_STANDBY as defined by
	 * spc4r17 section 5.9.2.4.4
	 */
	switch (cdb[0]) {
	case INQUIRY:
	case LOG_SELECT:
	case LOG_SENSE:
	case MODE_SELECT:
	case MODE_SENSE:
	case REPORT_LUNS:
	case RECEIVE_DIAGNOSTIC:
	case SEND_DIAGNOSTIC:
	case READ_CAPACITY:
		return 0;
	case SERVICE_ACTION_IN_16:
		switch (cdb[1] & 0x1f) {
		case SAI_READ_CAPACITY_16:
			return 0;
		default:
			set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_STANDBY);
			return 1;
		}
	case MAINTENANCE_IN:
		switch (cdb[1] & 0x1f) {
		case MI_REPORT_TARGET_PGS:
			return 0;
		default:
			set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_STANDBY);
			return 1;
		}
	case MAINTENANCE_OUT:
		switch (cdb[1]) {
		case MO_SET_TARGET_PGS:
			return 0;
		default:
			set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_STANDBY);
			return 1;
		}
	case REQUEST_SENSE:
	case PERSISTENT_RESERVE_IN:
	case PERSISTENT_RESERVE_OUT:
	case READ_BUFFER:
	case WRITE_BUFFER:
		return 0;
	default:
		set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_STANDBY);
		return 1;
	}

	return 0;
}