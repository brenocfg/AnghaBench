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
 int /*<<< orphan*/  ASCQ_04H_ALUA_STATE_TRANSITION ; 
#define  INQUIRY 134 
#define  MAINTENANCE_IN 133 
#define  MI_REPORT_TARGET_PGS 132 
#define  READ_BUFFER 131 
#define  REPORT_LUNS 130 
#define  REQUEST_SENSE 129 
#define  WRITE_BUFFER 128 
 int /*<<< orphan*/  set_ascq (struct se_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int core_alua_state_transition(
	struct se_cmd *cmd,
	unsigned char *cdb)
{
	/*
	 * Allowed CDBs for ALUA_ACCESS_STATE_TRANSITION as defined by
	 * spc4r17 section 5.9.2.5
	 */
	switch (cdb[0]) {
	case INQUIRY:
	case REPORT_LUNS:
		return 0;
	case MAINTENANCE_IN:
		switch (cdb[1] & 0x1f) {
		case MI_REPORT_TARGET_PGS:
			return 0;
		default:
			set_ascq(cmd, ASCQ_04H_ALUA_STATE_TRANSITION);
			return 1;
		}
	case REQUEST_SENSE:
	case READ_BUFFER:
	case WRITE_BUFFER:
		return 0;
	default:
		set_ascq(cmd, ASCQ_04H_ALUA_STATE_TRANSITION);
		return 1;
	}

	return 0;
}