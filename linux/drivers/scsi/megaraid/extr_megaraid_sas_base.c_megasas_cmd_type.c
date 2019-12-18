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
struct scsi_cmnd {int* cmnd; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEGASAS_IS_LOGICAL (int /*<<< orphan*/ ) ; 
 int NON_READ_WRITE_LDIO ; 
 int NON_READ_WRITE_SYSPDIO ; 
#define  READ_10 135 
#define  READ_12 134 
#define  READ_16 133 
#define  READ_6 132 
 int READ_WRITE_LDIO ; 
 int READ_WRITE_SYSPDIO ; 
#define  WRITE_10 131 
#define  WRITE_12 130 
#define  WRITE_16 129 
#define  WRITE_6 128 

inline int megasas_cmd_type(struct scsi_cmnd *cmd)
{
	int ret;

	switch (cmd->cmnd[0]) {
	case READ_10:
	case WRITE_10:
	case READ_12:
	case WRITE_12:
	case READ_6:
	case WRITE_6:
	case READ_16:
	case WRITE_16:
		ret = (MEGASAS_IS_LOGICAL(cmd->device)) ?
			READ_WRITE_LDIO : READ_WRITE_SYSPDIO;
		break;
	default:
		ret = (MEGASAS_IS_LOGICAL(cmd->device)) ?
			NON_READ_WRITE_LDIO : NON_READ_WRITE_SYSPDIO;
	}
	return ret;
}