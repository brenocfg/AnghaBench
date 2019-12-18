#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bnx2x_virtf {scalar_t__ state; int /*<<< orphan*/  abs_vfid; } ;
struct TYPE_9__ {int type; int /*<<< orphan*/  length; } ;
struct TYPE_10__ {TYPE_4__ tl; } ;
struct bnx2x_vf_mbx {TYPE_5__ first_tlv; TYPE_3__* msg; } ;
struct bnx2x {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * tlv_buffer; } ;
struct TYPE_7__ {TYPE_1__ tlv_buf_size; } ;
struct TYPE_8__ {TYPE_2__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
#define  CHANNEL_TLV_ACQUIRE 136 
#define  CHANNEL_TLV_CLOSE 135 
#define  CHANNEL_TLV_INIT 134 
#define  CHANNEL_TLV_RELEASE 133 
#define  CHANNEL_TLV_SETUP_Q 132 
#define  CHANNEL_TLV_SET_Q_FILTERS 131 
#define  CHANNEL_TLV_TEARDOWN_Q 130 
#define  CHANNEL_TLV_UPDATE_RSS 129 
#define  CHANNEL_TLV_UPDATE_TPA 128 
 int /*<<< orphan*/  DP_CONT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFVF_STATUS_NOT_SUPPORTED ; 
 scalar_t__ VF_ACQUIRED ; 
 scalar_t__ VF_ENABLED ; 
 int /*<<< orphan*/  bnx2x_lock_vf_pf_channel (struct bnx2x*,struct bnx2x_virtf*,int) ; 
 scalar_t__ bnx2x_tlv_supported (int) ; 
 int /*<<< orphan*/  bnx2x_unlock_vf_pf_channel (struct bnx2x*,struct bnx2x_virtf*,int) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_acquire (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_close_vf (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_init_vf (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_release_vf (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_resp (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_set_q_filters (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_setup_q (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_teardown_q (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_update_rss (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_update_tpa (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*) ; 
 int /*<<< orphan*/  storm_memset_vf_mbx_ack (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_vf_mbx_request(struct bnx2x *bp, struct bnx2x_virtf *vf,
				  struct bnx2x_vf_mbx *mbx)
{
	int i;

	/* check if tlv type is known */
	if (bnx2x_tlv_supported(mbx->first_tlv.tl.type)) {
		/* Lock the per vf op mutex and note the locker's identity.
		 * The unlock will take place in mbx response.
		 */
		bnx2x_lock_vf_pf_channel(bp, vf, mbx->first_tlv.tl.type);

		/* switch on the opcode */
		switch (mbx->first_tlv.tl.type) {
		case CHANNEL_TLV_ACQUIRE:
			bnx2x_vf_mbx_acquire(bp, vf, mbx);
			return;
		case CHANNEL_TLV_INIT:
			bnx2x_vf_mbx_init_vf(bp, vf, mbx);
			return;
		case CHANNEL_TLV_SETUP_Q:
			bnx2x_vf_mbx_setup_q(bp, vf, mbx);
			return;
		case CHANNEL_TLV_SET_Q_FILTERS:
			bnx2x_vf_mbx_set_q_filters(bp, vf, mbx);
			return;
		case CHANNEL_TLV_TEARDOWN_Q:
			bnx2x_vf_mbx_teardown_q(bp, vf, mbx);
			return;
		case CHANNEL_TLV_CLOSE:
			bnx2x_vf_mbx_close_vf(bp, vf, mbx);
			return;
		case CHANNEL_TLV_RELEASE:
			bnx2x_vf_mbx_release_vf(bp, vf, mbx);
			return;
		case CHANNEL_TLV_UPDATE_RSS:
			bnx2x_vf_mbx_update_rss(bp, vf, mbx);
			return;
		case CHANNEL_TLV_UPDATE_TPA:
			bnx2x_vf_mbx_update_tpa(bp, vf, mbx);
			return;
		}

	} else {
		/* unknown TLV - this may belong to a VF driver from the future
		 * - a version written after this PF driver was written, which
		 * supports features unknown as of yet. Too bad since we don't
		 * support them. Or this may be because someone wrote a crappy
		 * VF driver and is sending garbage over the channel.
		 */
		BNX2X_ERR("unknown TLV. type %d length %d vf->state was %d. first 20 bytes of mailbox buffer:\n",
			  mbx->first_tlv.tl.type, mbx->first_tlv.tl.length,
			  vf->state);
		for (i = 0; i < 20; i++)
			DP_CONT(BNX2X_MSG_IOV, "%x ",
				mbx->msg->req.tlv_buf_size.tlv_buffer[i]);
	}

	/* can we respond to VF (do we have an address for it?) */
	if (vf->state == VF_ACQUIRED || vf->state == VF_ENABLED) {
		/* notify the VF that we do not support this request */
		bnx2x_vf_mbx_resp(bp, vf, PFVF_STATUS_NOT_SUPPORTED);
	} else {
		/* can't send a response since this VF is unknown to us
		 * just ack the FW to release the mailbox and unlock
		 * the channel.
		 */
		storm_memset_vf_mbx_ack(bp, vf->abs_vfid);
		/* Firmware ack should be written before unlocking channel */
		bnx2x_unlock_vf_pf_channel(bp, vf, mbx->first_tlv.tl.type);
	}
}