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
typedef  int u8 ;

/* Variables and functions */
#define  MLXSW_CMD_STATUS_BAD_INDEX 140 
#define  MLXSW_CMD_STATUS_BAD_NVMEM 139 
#define  MLXSW_CMD_STATUS_BAD_OP 138 
#define  MLXSW_CMD_STATUS_BAD_PARAM 137 
#define  MLXSW_CMD_STATUS_BAD_PKT 136 
#define  MLXSW_CMD_STATUS_BAD_RESOURCE 135 
#define  MLXSW_CMD_STATUS_BAD_RES_STATE 134 
#define  MLXSW_CMD_STATUS_BAD_SYS_STATE 133 
#define  MLXSW_CMD_STATUS_EXCEED_LIM 132 
#define  MLXSW_CMD_STATUS_INTERNAL_ERR 131 
#define  MLXSW_CMD_STATUS_OK 130 
#define  MLXSW_CMD_STATUS_RESOURCE_BUSY 129 
#define  MLXSW_CMD_STATUS_RUNNING_RESET 128 

__attribute__((used)) static inline const char *mlxsw_cmd_status_str(u8 status)
{
	switch (status) {
	case MLXSW_CMD_STATUS_OK:
		return "OK";
	case MLXSW_CMD_STATUS_INTERNAL_ERR:
		return "INTERNAL_ERR";
	case MLXSW_CMD_STATUS_BAD_OP:
		return "BAD_OP";
	case MLXSW_CMD_STATUS_BAD_PARAM:
		return "BAD_PARAM";
	case MLXSW_CMD_STATUS_BAD_SYS_STATE:
		return "BAD_SYS_STATE";
	case MLXSW_CMD_STATUS_BAD_RESOURCE:
		return "BAD_RESOURCE";
	case MLXSW_CMD_STATUS_RESOURCE_BUSY:
		return "RESOURCE_BUSY";
	case MLXSW_CMD_STATUS_EXCEED_LIM:
		return "EXCEED_LIM";
	case MLXSW_CMD_STATUS_BAD_RES_STATE:
		return "BAD_RES_STATE";
	case MLXSW_CMD_STATUS_BAD_INDEX:
		return "BAD_INDEX";
	case MLXSW_CMD_STATUS_BAD_NVMEM:
		return "BAD_NVMEM";
	case MLXSW_CMD_STATUS_RUNNING_RESET:
		return "RUNNING_RESET";
	case MLXSW_CMD_STATUS_BAD_PKT:
		return "BAD_PKT";
	default:
		return "*UNKNOWN*";
	}
}