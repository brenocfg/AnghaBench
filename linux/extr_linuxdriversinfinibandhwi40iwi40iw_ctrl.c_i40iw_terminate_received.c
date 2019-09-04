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
typedef  int /*<<< orphan*/  u16 ;
struct i40iw_terminate_hdr {scalar_t__ layer_etype; } ;
struct i40iw_sc_qp {int* q2_buf; int /*<<< orphan*/  eventtype; int /*<<< orphan*/  term_flags; } ;
struct i40iw_aeqe_info {int /*<<< orphan*/  ae_id; scalar_t__ q2_data_written; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_AE_DDP_INVALID_MSN_GAP_IN_MSN ; 
 int /*<<< orphan*/  I40IW_AE_DDP_UBE_INVALID_DDP_VERSION ; 
 int /*<<< orphan*/  I40IW_AE_DDP_UBE_INVALID_MO ; 
 int /*<<< orphan*/  I40IW_AE_DDP_UBE_INVALID_QN ; 
 int /*<<< orphan*/  I40IW_AE_LCE_QP_CATASTROPHIC ; 
 int /*<<< orphan*/  I40IW_AE_RDMAP_ROE_INVALID_RDMAP_VERSION ; 
 int /*<<< orphan*/  I40IW_TERM_RCVD ; 
 int Q2_BAD_FRAME_OFFSET ; 
 scalar_t__ RDMAP_REMOTE_OP ; 
 scalar_t__ RDMAP_REMOTE_PROT ; 
 int /*<<< orphan*/  TERM_EVENT_QP_FATAL ; 
 scalar_t__ i40iw_locate_mpa (int*) ; 
 int /*<<< orphan*/  i40iw_terminate_connection (struct i40iw_sc_qp*,struct i40iw_aeqe_info*) ; 
 int /*<<< orphan*/  i40iw_terminate_done (struct i40iw_sc_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_terminate_send_fin (struct i40iw_sc_qp*) ; 
 int /*<<< orphan*/  i40iw_terminate_start_timer (struct i40iw_sc_qp*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

void i40iw_terminate_received(struct i40iw_sc_qp *qp, struct i40iw_aeqe_info *info)
{
	u8 *pkt = qp->q2_buf + Q2_BAD_FRAME_OFFSET;
	__be32 *mpa;
	u8 ddp_ctl;
	u8 rdma_ctl;
	u16 aeq_id = 0;
	struct i40iw_terminate_hdr *termhdr;

	mpa = (__be32 *)i40iw_locate_mpa(pkt);
	if (info->q2_data_written) {
		/* did not validate the frame - do it now */
		ddp_ctl = (ntohl(mpa[0]) >> 8) & 0xff;
		rdma_ctl = ntohl(mpa[0]) & 0xff;
		if ((ddp_ctl & 0xc0) != 0x40)
			aeq_id = I40IW_AE_LCE_QP_CATASTROPHIC;
		else if ((ddp_ctl & 0x03) != 1)
			aeq_id = I40IW_AE_DDP_UBE_INVALID_DDP_VERSION;
		else if (ntohl(mpa[2]) != 2)
			aeq_id = I40IW_AE_DDP_UBE_INVALID_QN;
		else if (ntohl(mpa[3]) != 1)
			aeq_id = I40IW_AE_DDP_INVALID_MSN_GAP_IN_MSN;
		else if (ntohl(mpa[4]) != 0)
			aeq_id = I40IW_AE_DDP_UBE_INVALID_MO;
		else if ((rdma_ctl & 0xc0) != 0x40)
			aeq_id = I40IW_AE_RDMAP_ROE_INVALID_RDMAP_VERSION;

		info->ae_id = aeq_id;
		if (info->ae_id) {
			/* Bad terminate recvd - send back a terminate */
			i40iw_terminate_connection(qp, info);
			return;
		}
	}

	qp->term_flags |= I40IW_TERM_RCVD;
	qp->eventtype = TERM_EVENT_QP_FATAL;
	termhdr = (struct i40iw_terminate_hdr *)&mpa[5];
	if (termhdr->layer_etype == RDMAP_REMOTE_PROT ||
	    termhdr->layer_etype == RDMAP_REMOTE_OP) {
		i40iw_terminate_done(qp, 0);
	} else {
		i40iw_terminate_start_timer(qp);
		i40iw_terminate_send_fin(qp);
	}
}