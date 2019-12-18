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
typedef  enum mlxsw_emad_op_tlv_status { ____Placeholder_mlxsw_emad_op_tlv_status } mlxsw_emad_op_tlv_status ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
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
 int mlxsw_emad_op_tlv_status_get (char*) ; 

__attribute__((used)) static int mlxsw_emad_process_status(char *op_tlv,
				     enum mlxsw_emad_op_tlv_status *p_status)
{
	*p_status = mlxsw_emad_op_tlv_status_get(op_tlv);

	switch (*p_status) {
	case MLXSW_EMAD_OP_TLV_STATUS_SUCCESS:
		return 0;
	case MLXSW_EMAD_OP_TLV_STATUS_BUSY:
	case MLXSW_EMAD_OP_TLV_STATUS_MESSAGE_RECEIPT_ACK:
		return -EAGAIN;
	case MLXSW_EMAD_OP_TLV_STATUS_VERSION_NOT_SUPPORTED:
	case MLXSW_EMAD_OP_TLV_STATUS_UNKNOWN_TLV:
	case MLXSW_EMAD_OP_TLV_STATUS_REGISTER_NOT_SUPPORTED:
	case MLXSW_EMAD_OP_TLV_STATUS_CLASS_NOT_SUPPORTED:
	case MLXSW_EMAD_OP_TLV_STATUS_METHOD_NOT_SUPPORTED:
	case MLXSW_EMAD_OP_TLV_STATUS_BAD_PARAMETER:
	case MLXSW_EMAD_OP_TLV_STATUS_RESOURCE_NOT_AVAILABLE:
	case MLXSW_EMAD_OP_TLV_STATUS_INTERNAL_ERROR:
	default:
		return -EIO;
	}
}