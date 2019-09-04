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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct i40iw_terminate_hdr {int /*<<< orphan*/  hdrct; } ;
struct i40iw_sc_qp {int* q2_buf; void* eventtype; } ;
struct i40iw_aeqe_info {int ae_id; scalar_t__ q2_data_written; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int DDP_CATASTROPHIC ; 
 int /*<<< orphan*/  DDP_CATASTROPHIC_LOCAL ; 
 int /*<<< orphan*/  DDP_HDR_FLAG ; 
 int /*<<< orphan*/  DDP_LEN_FLAG ; 
 int DDP_LLP ; 
 int /*<<< orphan*/  DDP_TAGGED_BOUNDS ; 
 int DDP_TAGGED_BUFFER ; 
 int /*<<< orphan*/  DDP_TAGGED_INV_DDP_VER ; 
 int /*<<< orphan*/  DDP_TAGGED_INV_STAG ; 
 int /*<<< orphan*/  DDP_TAGGED_UNASSOC_STAG ; 
 int DDP_UNTAGGED_BUFFER ; 
 int /*<<< orphan*/  DDP_UNTAGGED_INV_DDP_VER ; 
 int /*<<< orphan*/  DDP_UNTAGGED_INV_MO ; 
 int /*<<< orphan*/  DDP_UNTAGGED_INV_MSN_NO_BUF ; 
 int /*<<< orphan*/  DDP_UNTAGGED_INV_MSN_RANGE ; 
 int /*<<< orphan*/  DDP_UNTAGGED_INV_QN ; 
 int /*<<< orphan*/  DDP_UNTAGGED_INV_TOO_LONG ; 
 int /*<<< orphan*/  FLUSH_FATAL_ERR ; 
 int /*<<< orphan*/  FLUSH_GENERAL_ERR ; 
 int /*<<< orphan*/  FLUSH_LOC_LEN_ERR ; 
 int /*<<< orphan*/  FLUSH_LOC_QP_OP_ERR ; 
 int /*<<< orphan*/  FLUSH_PROT_ERR ; 
 int /*<<< orphan*/  FLUSH_REM_ACCESS_ERR ; 
 int /*<<< orphan*/  FLUSH_REM_OP_ERR ; 
#define  I40IW_AE_AMP_BAD_PD 154 
#define  I40IW_AE_AMP_BAD_QP 153 
#define  I40IW_AE_AMP_BAD_STAG_INDEX 152 
#define  I40IW_AE_AMP_BAD_STAG_KEY 151 
#define  I40IW_AE_AMP_BOUNDS_VIOLATION 150 
#define  I40IW_AE_AMP_INVALIDATE_NO_REMOTE_ACCESS_RIGHTS 149 
#define  I40IW_AE_AMP_INVALID_STAG 148 
#define  I40IW_AE_AMP_RIGHTS_VIOLATION 147 
#define  I40IW_AE_AMP_TO_WRAP 146 
#define  I40IW_AE_AMP_UNALLOCATED_STAG 145 
#define  I40IW_AE_DDP_INVALID_MSN_GAP_IN_MSN 144 
#define  I40IW_AE_DDP_NO_L_BIT 143 
#define  I40IW_AE_DDP_UBE_DDP_MESSAGE_TOO_LONG_FOR_AVAILABLE_BUFFER 142 
#define  I40IW_AE_DDP_UBE_INVALID_DDP_VERSION 141 
#define  I40IW_AE_DDP_UBE_INVALID_MO 140 
#define  I40IW_AE_DDP_UBE_INVALID_MSN_NO_BUFFER_AVAILABLE 139 
#define  I40IW_AE_DDP_UBE_INVALID_QN 138 
#define  I40IW_AE_LCE_QP_CATASTROPHIC 137 
#define  I40IW_AE_LLP_RECEIVED_MPA_CRC_ERROR 136 
#define  I40IW_AE_LLP_SEGMENT_TOO_LARGE 135 
#define  I40IW_AE_LLP_SEGMENT_TOO_SMALL 134 
#define  I40IW_AE_PRIV_OPERATION_DENIED 133 
#define  I40IW_AE_RDMAP_ROE_INVALID_RDMAP_VERSION 132 
#define  I40IW_AE_RDMAP_ROE_UNEXPECTED_OPCODE 131 
#define  I40IW_OP_TYPE_RDMA_WRITE 130 
#define  I40IW_OP_TYPE_SEND_INV 129 
#define  I40IW_OP_TYPE_SEND_SOL_INV 128 
 int LAYER_DDP ; 
 int LAYER_MPA ; 
 int LAYER_RDMA ; 
 int /*<<< orphan*/  MPA_CRC ; 
 int Q2_BAD_FRAME_OFFSET ; 
 int /*<<< orphan*/  RDMAP_ACCESS ; 
 int /*<<< orphan*/  RDMAP_CANT_INV_STAG ; 
 int /*<<< orphan*/  RDMAP_INV_BOUNDS ; 
 int /*<<< orphan*/  RDMAP_INV_RDMAP_VER ; 
 int /*<<< orphan*/  RDMAP_INV_STAG ; 
 int RDMAP_REMOTE_OP ; 
 int RDMAP_REMOTE_PROT ; 
 int /*<<< orphan*/  RDMAP_TO_WRAP ; 
 int /*<<< orphan*/  RDMAP_UNASSOC_STAG ; 
 int /*<<< orphan*/  RDMAP_UNEXPECTED_OP ; 
 int /*<<< orphan*/  RDMAP_UNSPECIFIED ; 
 int /*<<< orphan*/  RDMA_HDR_FLAG ; 
 int RDMA_OPCODE_MASK ; 
 int RDMA_READ_REQ_OPCODE ; 
 scalar_t__ TERM_DDP_LEN_TAGGED ; 
 scalar_t__ TERM_DDP_LEN_UNTAGGED ; 
 void* TERM_EVENT_QP_ACCESS_ERR ; 
 scalar_t__ TERM_RDMA_LEN ; 
 int i40iw_iwarp_opcode (struct i40iw_aeqe_info*,int*) ; 
 int* i40iw_locate_mpa (int*) ; 
 int /*<<< orphan*/  i40iw_setup_termhdr (struct i40iw_sc_qp*,struct i40iw_terminate_hdr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct i40iw_terminate_hdr*,int*,int) ; 
 int /*<<< orphan*/  memset (struct i40iw_terminate_hdr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40iw_bld_terminate_hdr(struct i40iw_sc_qp *qp,
				   struct i40iw_aeqe_info *info)
{
	u8 *pkt = qp->q2_buf + Q2_BAD_FRAME_OFFSET;
	u16 ddp_seg_len;
	int copy_len = 0;
	u8 is_tagged = 0;
	u32 opcode;
	struct i40iw_terminate_hdr *termhdr;

	termhdr = (struct i40iw_terminate_hdr *)qp->q2_buf;
	memset(termhdr, 0, Q2_BAD_FRAME_OFFSET);

	if (info->q2_data_written) {
		/* Use data from offending packet to fill in ddp & rdma hdrs */
		pkt = i40iw_locate_mpa(pkt);
		ddp_seg_len = ntohs(*(__be16 *)pkt);
		if (ddp_seg_len) {
			copy_len = 2;
			termhdr->hdrct = DDP_LEN_FLAG;
			if (pkt[2] & 0x80) {
				is_tagged = 1;
				if (ddp_seg_len >= TERM_DDP_LEN_TAGGED) {
					copy_len += TERM_DDP_LEN_TAGGED;
					termhdr->hdrct |= DDP_HDR_FLAG;
				}
			} else {
				if (ddp_seg_len >= TERM_DDP_LEN_UNTAGGED) {
					copy_len += TERM_DDP_LEN_UNTAGGED;
					termhdr->hdrct |= DDP_HDR_FLAG;
				}

				if (ddp_seg_len >= (TERM_DDP_LEN_UNTAGGED + TERM_RDMA_LEN)) {
					if ((pkt[3] & RDMA_OPCODE_MASK) == RDMA_READ_REQ_OPCODE) {
						copy_len += TERM_RDMA_LEN;
						termhdr->hdrct |= RDMA_HDR_FLAG;
					}
				}
			}
		}
	}

	opcode = i40iw_iwarp_opcode(info, pkt);

	switch (info->ae_id) {
	case I40IW_AE_AMP_UNALLOCATED_STAG:
		qp->eventtype = TERM_EVENT_QP_ACCESS_ERR;
		if (opcode == I40IW_OP_TYPE_RDMA_WRITE)
			i40iw_setup_termhdr(qp, termhdr, FLUSH_PROT_ERR,
					    (LAYER_DDP << 4) | DDP_TAGGED_BUFFER, DDP_TAGGED_INV_STAG);
		else
			i40iw_setup_termhdr(qp, termhdr, FLUSH_REM_ACCESS_ERR,
					    (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT, RDMAP_INV_STAG);
		break;
	case I40IW_AE_AMP_BOUNDS_VIOLATION:
		qp->eventtype = TERM_EVENT_QP_ACCESS_ERR;
		if (info->q2_data_written)
			i40iw_setup_termhdr(qp, termhdr, FLUSH_PROT_ERR,
					    (LAYER_DDP << 4) | DDP_TAGGED_BUFFER, DDP_TAGGED_BOUNDS);
		else
			i40iw_setup_termhdr(qp, termhdr, FLUSH_REM_ACCESS_ERR,
					    (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT, RDMAP_INV_BOUNDS);
		break;
	case I40IW_AE_AMP_BAD_PD:
		switch (opcode) {
		case I40IW_OP_TYPE_RDMA_WRITE:
			i40iw_setup_termhdr(qp, termhdr, FLUSH_PROT_ERR,
					    (LAYER_DDP << 4) | DDP_TAGGED_BUFFER, DDP_TAGGED_UNASSOC_STAG);
			break;
		case I40IW_OP_TYPE_SEND_INV:
		case I40IW_OP_TYPE_SEND_SOL_INV:
			i40iw_setup_termhdr(qp, termhdr, FLUSH_REM_ACCESS_ERR,
					    (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT, RDMAP_CANT_INV_STAG);
			break;
		default:
			i40iw_setup_termhdr(qp, termhdr, FLUSH_REM_ACCESS_ERR,
					    (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT, RDMAP_UNASSOC_STAG);
		}
		break;
	case I40IW_AE_AMP_INVALID_STAG:
		qp->eventtype = TERM_EVENT_QP_ACCESS_ERR;
		i40iw_setup_termhdr(qp, termhdr, FLUSH_REM_ACCESS_ERR,
				    (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT, RDMAP_INV_STAG);
		break;
	case I40IW_AE_AMP_BAD_QP:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_LOC_QP_OP_ERR,
				    (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER, DDP_UNTAGGED_INV_QN);
		break;
	case I40IW_AE_AMP_BAD_STAG_KEY:
	case I40IW_AE_AMP_BAD_STAG_INDEX:
		qp->eventtype = TERM_EVENT_QP_ACCESS_ERR;
		switch (opcode) {
		case I40IW_OP_TYPE_SEND_INV:
		case I40IW_OP_TYPE_SEND_SOL_INV:
			i40iw_setup_termhdr(qp, termhdr, FLUSH_REM_OP_ERR,
					    (LAYER_RDMA << 4) | RDMAP_REMOTE_OP, RDMAP_CANT_INV_STAG);
			break;
		default:
			i40iw_setup_termhdr(qp, termhdr, FLUSH_REM_ACCESS_ERR,
					    (LAYER_RDMA << 4) | RDMAP_REMOTE_OP, RDMAP_INV_STAG);
		}
		break;
	case I40IW_AE_AMP_RIGHTS_VIOLATION:
	case I40IW_AE_AMP_INVALIDATE_NO_REMOTE_ACCESS_RIGHTS:
	case I40IW_AE_PRIV_OPERATION_DENIED:
		qp->eventtype = TERM_EVENT_QP_ACCESS_ERR;
		i40iw_setup_termhdr(qp, termhdr, FLUSH_REM_ACCESS_ERR,
				    (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT, RDMAP_ACCESS);
		break;
	case I40IW_AE_AMP_TO_WRAP:
		qp->eventtype = TERM_EVENT_QP_ACCESS_ERR;
		i40iw_setup_termhdr(qp, termhdr, FLUSH_REM_ACCESS_ERR,
				    (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT, RDMAP_TO_WRAP);
		break;
	case I40IW_AE_LLP_RECEIVED_MPA_CRC_ERROR:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_GENERAL_ERR,
				    (LAYER_MPA << 4) | DDP_LLP, MPA_CRC);
		break;
	case I40IW_AE_LLP_SEGMENT_TOO_LARGE:
	case I40IW_AE_LLP_SEGMENT_TOO_SMALL:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_LOC_LEN_ERR,
				    (LAYER_DDP << 4) | DDP_CATASTROPHIC, DDP_CATASTROPHIC_LOCAL);
		break;
	case I40IW_AE_LCE_QP_CATASTROPHIC:
	case I40IW_AE_DDP_NO_L_BIT:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_FATAL_ERR,
				    (LAYER_DDP << 4) | DDP_CATASTROPHIC, DDP_CATASTROPHIC_LOCAL);
		break;
	case I40IW_AE_DDP_INVALID_MSN_GAP_IN_MSN:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_GENERAL_ERR,
				    (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER, DDP_UNTAGGED_INV_MSN_RANGE);
		break;
	case I40IW_AE_DDP_UBE_DDP_MESSAGE_TOO_LONG_FOR_AVAILABLE_BUFFER:
		qp->eventtype = TERM_EVENT_QP_ACCESS_ERR;
		i40iw_setup_termhdr(qp, termhdr, FLUSH_LOC_LEN_ERR,
				    (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER, DDP_UNTAGGED_INV_TOO_LONG);
		break;
	case I40IW_AE_DDP_UBE_INVALID_DDP_VERSION:
		if (is_tagged)
			i40iw_setup_termhdr(qp, termhdr, FLUSH_GENERAL_ERR,
					    (LAYER_DDP << 4) | DDP_TAGGED_BUFFER, DDP_TAGGED_INV_DDP_VER);
		else
			i40iw_setup_termhdr(qp, termhdr, FLUSH_GENERAL_ERR,
					    (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER, DDP_UNTAGGED_INV_DDP_VER);
		break;
	case I40IW_AE_DDP_UBE_INVALID_MO:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_GENERAL_ERR,
				    (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER, DDP_UNTAGGED_INV_MO);
		break;
	case I40IW_AE_DDP_UBE_INVALID_MSN_NO_BUFFER_AVAILABLE:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_REM_OP_ERR,
				    (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER, DDP_UNTAGGED_INV_MSN_NO_BUF);
		break;
	case I40IW_AE_DDP_UBE_INVALID_QN:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_GENERAL_ERR,
				    (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER, DDP_UNTAGGED_INV_QN);
		break;
	case I40IW_AE_RDMAP_ROE_INVALID_RDMAP_VERSION:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_GENERAL_ERR,
				    (LAYER_RDMA << 4) | RDMAP_REMOTE_OP, RDMAP_INV_RDMAP_VER);
		break;
	case I40IW_AE_RDMAP_ROE_UNEXPECTED_OPCODE:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_LOC_QP_OP_ERR,
				    (LAYER_RDMA << 4) | RDMAP_REMOTE_OP, RDMAP_UNEXPECTED_OP);
		break;
	default:
		i40iw_setup_termhdr(qp, termhdr, FLUSH_FATAL_ERR,
				    (LAYER_RDMA << 4) | RDMAP_REMOTE_OP, RDMAP_UNSPECIFIED);
		break;
	}

	if (copy_len)
		memcpy(termhdr + 1, pkt, copy_len);

	return sizeof(struct i40iw_terminate_hdr) + copy_len;
}