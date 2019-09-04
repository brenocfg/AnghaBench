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
#define  MLXSW_EMAD_OP_TLV_STATUS_BAD_PARAMETER 138 
#define  MLXSW_EMAD_OP_TLV_STATUS_BUSY 137 
#define  MLXSW_EMAD_OP_TLV_STATUS_CLASS_NOT_SUPPORTED 136 
#define  MLXSW_EMAD_OP_TLV_STATUS_INTERNAL_ERROR 135 
#define  MLXSW_EMAD_OP_TLV_STATUS_MESSAGE_RECEIPT_ACK 134 
#define  MLXSW_EMAD_OP_TLV_STATUS_METHOD_NOT_SUPPORTED 133 
#define  MLXSW_EMAD_OP_TLV_STATUS_REGISTER_NOT_SUPPORTED 132 
#define  MLXSW_EMAD_OP_TLV_STATUS_RESOURCE_NOT_AVAILABLE 131 
#define  MLXSW_EMAD_OP_TLV_STATUS_SUCCESS 130 
#define  MLXSW_EMAD_OP_TLV_STATUS_UNKNOWN_TLV 129 
#define  MLXSW_EMAD_OP_TLV_STATUS_VERSION_NOT_SUPPORTED 128 

__attribute__((used)) static inline char *mlxsw_emad_op_tlv_status_str(u8 status)
{
	switch (status) {
	case MLXSW_EMAD_OP_TLV_STATUS_SUCCESS:
		return "operation performed";
	case MLXSW_EMAD_OP_TLV_STATUS_BUSY:
		return "device is busy";
	case MLXSW_EMAD_OP_TLV_STATUS_VERSION_NOT_SUPPORTED:
		return "version not supported";
	case MLXSW_EMAD_OP_TLV_STATUS_UNKNOWN_TLV:
		return "unknown TLV";
	case MLXSW_EMAD_OP_TLV_STATUS_REGISTER_NOT_SUPPORTED:
		return "register not supported";
	case MLXSW_EMAD_OP_TLV_STATUS_CLASS_NOT_SUPPORTED:
		return "class not supported";
	case MLXSW_EMAD_OP_TLV_STATUS_METHOD_NOT_SUPPORTED:
		return "method not supported";
	case MLXSW_EMAD_OP_TLV_STATUS_BAD_PARAMETER:
		return "bad parameter";
	case MLXSW_EMAD_OP_TLV_STATUS_RESOURCE_NOT_AVAILABLE:
		return "resource not available";
	case MLXSW_EMAD_OP_TLV_STATUS_MESSAGE_RECEIPT_ACK:
		return "acknowledged. retransmit";
	case MLXSW_EMAD_OP_TLV_STATUS_INTERNAL_ERROR:
		return "internal error";
	default:
		return "*UNKNOWN*";
	}
}