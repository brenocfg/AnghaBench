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
typedef  enum ionic_cmd_opcode { ____Placeholder_ionic_cmd_opcode } ionic_cmd_opcode ;

/* Variables and functions */
#define  IONIC_CMD_FW_CONTROL 154 
#define  IONIC_CMD_FW_DOWNLOAD 153 
#define  IONIC_CMD_GETATTR 152 
#define  IONIC_CMD_IDENTIFY 151 
#define  IONIC_CMD_INIT 150 
#define  IONIC_CMD_LIF_GETATTR 149 
#define  IONIC_CMD_LIF_IDENTIFY 148 
#define  IONIC_CMD_LIF_INIT 147 
#define  IONIC_CMD_LIF_RESET 146 
#define  IONIC_CMD_LIF_SETATTR 145 
#define  IONIC_CMD_NOP 144 
#define  IONIC_CMD_PORT_GETATTR 143 
#define  IONIC_CMD_PORT_IDENTIFY 142 
#define  IONIC_CMD_PORT_INIT 141 
#define  IONIC_CMD_PORT_RESET 140 
#define  IONIC_CMD_PORT_SETATTR 139 
#define  IONIC_CMD_Q_CONTROL 138 
#define  IONIC_CMD_Q_INIT 137 
#define  IONIC_CMD_RDMA_CREATE_ADMINQ 136 
#define  IONIC_CMD_RDMA_CREATE_CQ 135 
#define  IONIC_CMD_RDMA_CREATE_EQ 134 
#define  IONIC_CMD_RDMA_RESET_LIF 133 
#define  IONIC_CMD_RESET 132 
#define  IONIC_CMD_RX_FILTER_ADD 131 
#define  IONIC_CMD_RX_FILTER_DEL 130 
#define  IONIC_CMD_RX_MODE_SET 129 
#define  IONIC_CMD_SETATTR 128 

__attribute__((used)) static const char *ionic_opcode_to_str(enum ionic_cmd_opcode opcode)
{
	switch (opcode) {
	case IONIC_CMD_NOP:
		return "IONIC_CMD_NOP";
	case IONIC_CMD_INIT:
		return "IONIC_CMD_INIT";
	case IONIC_CMD_RESET:
		return "IONIC_CMD_RESET";
	case IONIC_CMD_IDENTIFY:
		return "IONIC_CMD_IDENTIFY";
	case IONIC_CMD_GETATTR:
		return "IONIC_CMD_GETATTR";
	case IONIC_CMD_SETATTR:
		return "IONIC_CMD_SETATTR";
	case IONIC_CMD_PORT_IDENTIFY:
		return "IONIC_CMD_PORT_IDENTIFY";
	case IONIC_CMD_PORT_INIT:
		return "IONIC_CMD_PORT_INIT";
	case IONIC_CMD_PORT_RESET:
		return "IONIC_CMD_PORT_RESET";
	case IONIC_CMD_PORT_GETATTR:
		return "IONIC_CMD_PORT_GETATTR";
	case IONIC_CMD_PORT_SETATTR:
		return "IONIC_CMD_PORT_SETATTR";
	case IONIC_CMD_LIF_INIT:
		return "IONIC_CMD_LIF_INIT";
	case IONIC_CMD_LIF_RESET:
		return "IONIC_CMD_LIF_RESET";
	case IONIC_CMD_LIF_IDENTIFY:
		return "IONIC_CMD_LIF_IDENTIFY";
	case IONIC_CMD_LIF_SETATTR:
		return "IONIC_CMD_LIF_SETATTR";
	case IONIC_CMD_LIF_GETATTR:
		return "IONIC_CMD_LIF_GETATTR";
	case IONIC_CMD_RX_MODE_SET:
		return "IONIC_CMD_RX_MODE_SET";
	case IONIC_CMD_RX_FILTER_ADD:
		return "IONIC_CMD_RX_FILTER_ADD";
	case IONIC_CMD_RX_FILTER_DEL:
		return "IONIC_CMD_RX_FILTER_DEL";
	case IONIC_CMD_Q_INIT:
		return "IONIC_CMD_Q_INIT";
	case IONIC_CMD_Q_CONTROL:
		return "IONIC_CMD_Q_CONTROL";
	case IONIC_CMD_RDMA_RESET_LIF:
		return "IONIC_CMD_RDMA_RESET_LIF";
	case IONIC_CMD_RDMA_CREATE_EQ:
		return "IONIC_CMD_RDMA_CREATE_EQ";
	case IONIC_CMD_RDMA_CREATE_CQ:
		return "IONIC_CMD_RDMA_CREATE_CQ";
	case IONIC_CMD_RDMA_CREATE_ADMINQ:
		return "IONIC_CMD_RDMA_CREATE_ADMINQ";
	case IONIC_CMD_FW_DOWNLOAD:
		return "IONIC_CMD_FW_DOWNLOAD";
	case IONIC_CMD_FW_CONTROL:
		return "IONIC_CMD_FW_CONTROL";
	default:
		return "DEVCMD_UNKNOWN";
	}
}