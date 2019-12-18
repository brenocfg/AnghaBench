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

/* Variables and functions */
#define  ACCESS_CONTROL_IN 168 
#define  ACCESS_CONTROL_OUT 167 
#define  ALLOW_MEDIUM_REMOVAL 166 
 int /*<<< orphan*/  CMD_DIR_MSG ; 
 int DMA_FROM_DEVICE ; 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 
 int EINVAL ; 
#define  ERASE 165 
#define  INQUIRY 164 
#define  MAINTENANCE_IN 163 
#define  MAINTENANCE_OUT 162 
#define  MODE_SELECT 161 
#define  MODE_SELECT_10 160 
#define  MODE_SENSE 159 
#define  MODE_SENSE_10 158 
#define  PERSISTENT_RESERVE_IN 157 
#define  PERSISTENT_RESERVE_OUT 156 
#define  READ_10 155 
#define  READ_12 154 
#define  READ_16 153 
#define  READ_6 152 
#define  READ_BLOCK_LIMITS 151 
#define  READ_CAPACITY 150 
#define  READ_FORMAT_CAPACITIES 149 
#define  READ_POSITION 148 
#define  READ_TOC 147 
#define  REPORT_LUNS 146 
#define  REQUEST_SENSE 145 
#define  REZERO_UNIT 144 
#define  SECURITY_PROTOCOL_IN 143 
#define  SECURITY_PROTOCOL_OUT 142 
#define  SEEK_10 141 
#define  SERVICE_ACTION_IN_16 140 
#define  SPACE 139 
#define  START_STOP 138 
#define  SYNCHRONIZE_CACHE 137 
#define  TEST_UNIT_READY 136 
#define  VERIFY 135 
#define  WRITE_10 134 
#define  WRITE_12 133 
#define  WRITE_16 132 
#define  WRITE_6 131 
#define  WRITE_FILEMARKS 130 
#define  WRITE_VERIFY 129 
#define  WRITE_VERIFY_12 128 
 int /*<<< orphan*/  pr_warn (int /*<<< orphan*/ ,unsigned char const) ; 

__attribute__((used)) static int get_cmd_dir(const unsigned char *cdb)
{
	int ret;

	switch (cdb[0]) {
	case READ_6:
	case READ_10:
	case READ_12:
	case READ_16:
	case INQUIRY:
	case MODE_SENSE:
	case MODE_SENSE_10:
	case SERVICE_ACTION_IN_16:
	case MAINTENANCE_IN:
	case PERSISTENT_RESERVE_IN:
	case SECURITY_PROTOCOL_IN:
	case ACCESS_CONTROL_IN:
	case REPORT_LUNS:
	case READ_BLOCK_LIMITS:
	case READ_POSITION:
	case READ_CAPACITY:
	case READ_TOC:
	case READ_FORMAT_CAPACITIES:
	case REQUEST_SENSE:
		ret = DMA_FROM_DEVICE;
		break;

	case WRITE_6:
	case WRITE_10:
	case WRITE_12:
	case WRITE_16:
	case MODE_SELECT:
	case MODE_SELECT_10:
	case WRITE_VERIFY:
	case WRITE_VERIFY_12:
	case PERSISTENT_RESERVE_OUT:
	case MAINTENANCE_OUT:
	case SECURITY_PROTOCOL_OUT:
	case ACCESS_CONTROL_OUT:
		ret = DMA_TO_DEVICE;
		break;
	case ALLOW_MEDIUM_REMOVAL:
	case TEST_UNIT_READY:
	case SYNCHRONIZE_CACHE:
	case START_STOP:
	case ERASE:
	case REZERO_UNIT:
	case SEEK_10:
	case SPACE:
	case VERIFY:
	case WRITE_FILEMARKS:
		ret = DMA_NONE;
		break;
	default:
#define CMD_DIR_MSG "target: Unknown data direction for SCSI Opcode 0x%02x\n"
		pr_warn(CMD_DIR_MSG, cdb[0]);
#undef CMD_DIR_MSG
		ret = -EINVAL;
	}
	return ret;
}