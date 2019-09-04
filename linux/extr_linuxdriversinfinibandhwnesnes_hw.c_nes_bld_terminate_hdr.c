#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct nes_terminate_hdr {int layer_etype; void* error_code; int /*<<< orphan*/  hdrct; } ;
struct TYPE_2__ {int* q2_vbase; } ;
struct nes_qp {int term_sq_flush_code; int term_rq_flush_code; TYPE_1__ hwqp; } ;

/* Variables and functions */
 int BAD_FRAME_OFFSET ; 
 int DDP_CATASTROPHIC ; 
 void* DDP_CATASTROPHIC_LOCAL ; 
 int /*<<< orphan*/  DDP_HDR_FLAG ; 
 int /*<<< orphan*/  DDP_LEN_FLAG ; 
 int DDP_LLP ; 
 void* DDP_TAGGED_BOUNDS ; 
 int DDP_TAGGED_BUFFER ; 
 void* DDP_TAGGED_INV_DDP_VER ; 
 void* DDP_TAGGED_INV_STAG ; 
 void* DDP_TAGGED_UNASSOC_STAG ; 
 int DDP_UNTAGGED_BUFFER ; 
 void* DDP_UNTAGGED_INV_DDP_VER ; 
 void* DDP_UNTAGGED_INV_MO ; 
 void* DDP_UNTAGGED_INV_MSN_NO_BUF ; 
 void* DDP_UNTAGGED_INV_MSN_RANGE ; 
 void* DDP_UNTAGGED_INV_QN ; 
 void* DDP_UNTAGGED_INV_TOO_LONG ; 
 int IB_WC_FATAL_ERR ; 
 int IB_WC_GENERAL_ERR ; 
 int IB_WC_LOC_LEN_ERR ; 
 int IB_WC_LOC_PROT_ERR ; 
 int IB_WC_LOC_QP_OP_ERR ; 
 int IB_WC_REM_ACCESS_ERR ; 
 int IB_WC_REM_OP_ERR ; 
#define  IWARP_OPCODE_SEND_INV 156 
#define  IWARP_OPCODE_SEND_SE_INV 155 
#define  IWARP_OPCODE_WRITE 154 
 int LAYER_DDP ; 
 int LAYER_MPA ; 
 int LAYER_RDMA ; 
 void* MPA_CRC ; 
 void* MPA_MARKER ; 
#define  NES_AEQE_AEID_AMP_BAD_PD 153 
#define  NES_AEQE_AEID_AMP_BAD_QP 152 
#define  NES_AEQE_AEID_AMP_BAD_STAG_INDEX 151 
#define  NES_AEQE_AEID_AMP_BAD_STAG_KEY 150 
#define  NES_AEQE_AEID_AMP_BOUNDS_VIOLATION 149 
#define  NES_AEQE_AEID_AMP_INVALIDATE_NO_REMOTE_ACCESS_RIGHTS 148 
#define  NES_AEQE_AEID_AMP_INVALID_STAG 147 
#define  NES_AEQE_AEID_AMP_RIGHTS_VIOLATION 146 
#define  NES_AEQE_AEID_AMP_TO_WRAP 145 
#define  NES_AEQE_AEID_AMP_UNALLOCATED_STAG 144 
#define  NES_AEQE_AEID_DDP_INVALID_MSN_GAP_IN_MSN 143 
#define  NES_AEQE_AEID_DDP_INVALID_MSN_RANGE_IS_NOT_VALID 142 
#define  NES_AEQE_AEID_DDP_LCE_LOCAL_CATASTROPHIC 141 
#define  NES_AEQE_AEID_DDP_NO_L_BIT 140 
#define  NES_AEQE_AEID_DDP_UBE_DDP_MESSAGE_TOO_LONG_FOR_AVAILABLE_BUFFER 139 
#define  NES_AEQE_AEID_DDP_UBE_INVALID_DDP_VERSION 138 
#define  NES_AEQE_AEID_DDP_UBE_INVALID_MO 137 
#define  NES_AEQE_AEID_DDP_UBE_INVALID_MSN_NO_BUFFER_AVAILABLE 136 
#define  NES_AEQE_AEID_DDP_UBE_INVALID_QN 135 
#define  NES_AEQE_AEID_LLP_RECEIVED_MARKER_AND_LENGTH_FIELDS_DONT_MATCH 134 
#define  NES_AEQE_AEID_LLP_RECEIVED_MPA_CRC_ERROR 133 
#define  NES_AEQE_AEID_LLP_SEGMENT_TOO_LARGE 132 
#define  NES_AEQE_AEID_LLP_SEGMENT_TOO_SMALL 131 
#define  NES_AEQE_AEID_PRIV_OPERATION_DENIED 130 
#define  NES_AEQE_AEID_RDMAP_ROE_INVALID_RDMAP_VERSION 129 
#define  NES_AEQE_AEID_RDMAP_ROE_UNEXPECTED_OPCODE 128 
 int NES_AEQE_INBOUND_RDMA ; 
 int NES_AEQE_Q2_DATA_ETHERNET ; 
 int NES_AEQE_Q2_DATA_MPA ; 
 int NES_AEQE_Q2_DATA_WRITTEN ; 
 int NES_AEQE_SQ ; 
 void* RDMAP_ACCESS ; 
 void* RDMAP_CANT_INV_STAG ; 
 void* RDMAP_INV_BOUNDS ; 
 void* RDMAP_INV_RDMAP_VER ; 
 void* RDMAP_INV_STAG ; 
 int RDMAP_REMOTE_OP ; 
 int RDMAP_REMOTE_PROT ; 
 void* RDMAP_TO_WRAP ; 
 void* RDMAP_UNASSOC_STAG ; 
 void* RDMAP_UNEXPECTED_OP ; 
 void* RDMAP_UNSPECIFIED ; 
 int /*<<< orphan*/  RDMA_HDR_FLAG ; 
 int RDMA_OPCODE_MASK ; 
 int RDMA_READ_REQ_OPCODE ; 
 scalar_t__ TERM_DDP_LEN_TAGGED ; 
 scalar_t__ TERM_DDP_LEN_UNTAGGED ; 
 scalar_t__ TERM_RDMA_LEN ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  iwarp_opcode (struct nes_qp*,int) ; 
 int* locate_mpa (int*,int) ; 
 int /*<<< orphan*/  memcpy (struct nes_terminate_hdr*,int*,int) ; 
 int /*<<< orphan*/  memset (struct nes_terminate_hdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nes_bld_terminate_hdr(struct nes_qp *nesqp, u16 async_event_id, u32 aeq_info)
{
	u8 *pkt = nesqp->hwqp.q2_vbase + BAD_FRAME_OFFSET;
	u16 ddp_seg_len;
	int copy_len = 0;
	u8 is_tagged = 0;
	u8 flush_code = 0;
	struct nes_terminate_hdr *termhdr;

	termhdr = (struct nes_terminate_hdr *)nesqp->hwqp.q2_vbase;
	memset(termhdr, 0, 64);

	if (aeq_info & NES_AEQE_Q2_DATA_WRITTEN) {

		/* Use data from offending packet to fill in ddp & rdma hdrs */
		pkt = locate_mpa(pkt, aeq_info);
		ddp_seg_len = be16_to_cpu(*(u16 *)pkt);
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

	switch (async_event_id) {
	case NES_AEQE_AEID_AMP_UNALLOCATED_STAG:
		switch (iwarp_opcode(nesqp, aeq_info)) {
		case IWARP_OPCODE_WRITE:
			flush_code = IB_WC_LOC_PROT_ERR;
			termhdr->layer_etype = (LAYER_DDP << 4) | DDP_TAGGED_BUFFER;
			termhdr->error_code = DDP_TAGGED_INV_STAG;
			break;
		default:
			flush_code = IB_WC_REM_ACCESS_ERR;
			termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT;
			termhdr->error_code = RDMAP_INV_STAG;
		}
		break;
	case NES_AEQE_AEID_AMP_INVALID_STAG:
		flush_code = IB_WC_REM_ACCESS_ERR;
		termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT;
		termhdr->error_code = RDMAP_INV_STAG;
		break;
	case NES_AEQE_AEID_AMP_BAD_QP:
		flush_code = IB_WC_LOC_QP_OP_ERR;
		termhdr->layer_etype = (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER;
		termhdr->error_code = DDP_UNTAGGED_INV_QN;
		break;
	case NES_AEQE_AEID_AMP_BAD_STAG_KEY:
	case NES_AEQE_AEID_AMP_BAD_STAG_INDEX:
		switch (iwarp_opcode(nesqp, aeq_info)) {
		case IWARP_OPCODE_SEND_INV:
		case IWARP_OPCODE_SEND_SE_INV:
			flush_code = IB_WC_REM_OP_ERR;
			termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_OP;
			termhdr->error_code = RDMAP_CANT_INV_STAG;
			break;
		default:
			flush_code = IB_WC_REM_ACCESS_ERR;
			termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT;
			termhdr->error_code = RDMAP_INV_STAG;
		}
		break;
	case NES_AEQE_AEID_AMP_BOUNDS_VIOLATION:
		if (aeq_info & (NES_AEQE_Q2_DATA_ETHERNET | NES_AEQE_Q2_DATA_MPA)) {
			flush_code = IB_WC_LOC_PROT_ERR;
			termhdr->layer_etype = (LAYER_DDP << 4) | DDP_TAGGED_BUFFER;
			termhdr->error_code = DDP_TAGGED_BOUNDS;
		} else {
			flush_code = IB_WC_REM_ACCESS_ERR;
			termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT;
			termhdr->error_code = RDMAP_INV_BOUNDS;
		}
		break;
	case NES_AEQE_AEID_AMP_RIGHTS_VIOLATION:
	case NES_AEQE_AEID_AMP_INVALIDATE_NO_REMOTE_ACCESS_RIGHTS:
	case NES_AEQE_AEID_PRIV_OPERATION_DENIED:
		flush_code = IB_WC_REM_ACCESS_ERR;
		termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT;
		termhdr->error_code = RDMAP_ACCESS;
		break;
	case NES_AEQE_AEID_AMP_TO_WRAP:
		flush_code = IB_WC_REM_ACCESS_ERR;
		termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT;
		termhdr->error_code = RDMAP_TO_WRAP;
		break;
	case NES_AEQE_AEID_AMP_BAD_PD:
		switch (iwarp_opcode(nesqp, aeq_info)) {
		case IWARP_OPCODE_WRITE:
			flush_code = IB_WC_LOC_PROT_ERR;
			termhdr->layer_etype = (LAYER_DDP << 4) | DDP_TAGGED_BUFFER;
			termhdr->error_code = DDP_TAGGED_UNASSOC_STAG;
			break;
		case IWARP_OPCODE_SEND_INV:
		case IWARP_OPCODE_SEND_SE_INV:
			flush_code = IB_WC_REM_ACCESS_ERR;
			termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT;
			termhdr->error_code = RDMAP_CANT_INV_STAG;
			break;
		default:
			flush_code = IB_WC_REM_ACCESS_ERR;
			termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_PROT;
			termhdr->error_code = RDMAP_UNASSOC_STAG;
		}
		break;
	case NES_AEQE_AEID_LLP_RECEIVED_MARKER_AND_LENGTH_FIELDS_DONT_MATCH:
		flush_code = IB_WC_LOC_LEN_ERR;
		termhdr->layer_etype = (LAYER_MPA << 4) | DDP_LLP;
		termhdr->error_code = MPA_MARKER;
		break;
	case NES_AEQE_AEID_LLP_RECEIVED_MPA_CRC_ERROR:
		flush_code = IB_WC_GENERAL_ERR;
		termhdr->layer_etype = (LAYER_MPA << 4) | DDP_LLP;
		termhdr->error_code = MPA_CRC;
		break;
	case NES_AEQE_AEID_LLP_SEGMENT_TOO_LARGE:
	case NES_AEQE_AEID_LLP_SEGMENT_TOO_SMALL:
		flush_code = IB_WC_LOC_LEN_ERR;
		termhdr->layer_etype = (LAYER_DDP << 4) | DDP_CATASTROPHIC;
		termhdr->error_code = DDP_CATASTROPHIC_LOCAL;
		break;
	case NES_AEQE_AEID_DDP_LCE_LOCAL_CATASTROPHIC:
	case NES_AEQE_AEID_DDP_NO_L_BIT:
		flush_code = IB_WC_FATAL_ERR;
		termhdr->layer_etype = (LAYER_DDP << 4) | DDP_CATASTROPHIC;
		termhdr->error_code = DDP_CATASTROPHIC_LOCAL;
		break;
	case NES_AEQE_AEID_DDP_INVALID_MSN_GAP_IN_MSN:
	case NES_AEQE_AEID_DDP_INVALID_MSN_RANGE_IS_NOT_VALID:
		flush_code = IB_WC_GENERAL_ERR;
		termhdr->layer_etype = (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER;
		termhdr->error_code = DDP_UNTAGGED_INV_MSN_RANGE;
		break;
	case NES_AEQE_AEID_DDP_UBE_DDP_MESSAGE_TOO_LONG_FOR_AVAILABLE_BUFFER:
		flush_code = IB_WC_LOC_LEN_ERR;
		termhdr->layer_etype = (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER;
		termhdr->error_code = DDP_UNTAGGED_INV_TOO_LONG;
		break;
	case NES_AEQE_AEID_DDP_UBE_INVALID_DDP_VERSION:
		flush_code = IB_WC_GENERAL_ERR;
		if (is_tagged) {
			termhdr->layer_etype = (LAYER_DDP << 4) | DDP_TAGGED_BUFFER;
			termhdr->error_code = DDP_TAGGED_INV_DDP_VER;
		} else {
			termhdr->layer_etype = (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER;
			termhdr->error_code = DDP_UNTAGGED_INV_DDP_VER;
		}
		break;
	case NES_AEQE_AEID_DDP_UBE_INVALID_MO:
		flush_code = IB_WC_GENERAL_ERR;
		termhdr->layer_etype = (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER;
		termhdr->error_code = DDP_UNTAGGED_INV_MO;
		break;
	case NES_AEQE_AEID_DDP_UBE_INVALID_MSN_NO_BUFFER_AVAILABLE:
		flush_code = IB_WC_REM_OP_ERR;
		termhdr->layer_etype = (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER;
		termhdr->error_code = DDP_UNTAGGED_INV_MSN_NO_BUF;
		break;
	case NES_AEQE_AEID_DDP_UBE_INVALID_QN:
		flush_code = IB_WC_GENERAL_ERR;
		termhdr->layer_etype = (LAYER_DDP << 4) | DDP_UNTAGGED_BUFFER;
		termhdr->error_code = DDP_UNTAGGED_INV_QN;
		break;
	case NES_AEQE_AEID_RDMAP_ROE_INVALID_RDMAP_VERSION:
		flush_code = IB_WC_GENERAL_ERR;
		termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_OP;
		termhdr->error_code = RDMAP_INV_RDMAP_VER;
		break;
	case NES_AEQE_AEID_RDMAP_ROE_UNEXPECTED_OPCODE:
		flush_code = IB_WC_LOC_QP_OP_ERR;
		termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_OP;
		termhdr->error_code = RDMAP_UNEXPECTED_OP;
		break;
	default:
		flush_code = IB_WC_FATAL_ERR;
		termhdr->layer_etype = (LAYER_RDMA << 4) | RDMAP_REMOTE_OP;
		termhdr->error_code = RDMAP_UNSPECIFIED;
		break;
	}

	if (copy_len)
		memcpy(termhdr + 1, pkt, copy_len);

	if ((flush_code) && ((NES_AEQE_INBOUND_RDMA & aeq_info) == 0)) {
		if (aeq_info & NES_AEQE_SQ)
			nesqp->term_sq_flush_code = flush_code;
		else
			nesqp->term_rq_flush_code = flush_code;
	}

	return sizeof(struct nes_terminate_hdr) + copy_len;
}