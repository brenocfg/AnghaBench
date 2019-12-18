#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {scalar_t__ paylen_newwin; scalar_t__ seg_num; int /*<<< orphan*/  rmpp_status; int /*<<< orphan*/  rmpp_type; int /*<<< orphan*/  rmpp_version; } ;
struct TYPE_5__ {int /*<<< orphan*/  method; } ;
struct ib_rmpp_mad {TYPE_3__ rmpp_hdr; TYPE_2__ mad_hdr; } ;
struct ib_mad_send_buf {int /*<<< orphan*/  ah; int /*<<< orphan*/  hdr_len; struct ib_rmpp_mad* mad; } ;
struct TYPE_4__ {int /*<<< orphan*/  mad; } ;
struct ib_mad_recv_wc {TYPE_1__ recv_buf; } ;
struct ib_mad_agent_private {int /*<<< orphan*/  agent; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MGMT_METHOD_RESP ; 
 int /*<<< orphan*/  IB_MGMT_RMPP_FLAG_ACTIVE ; 
 int /*<<< orphan*/  IB_MGMT_RMPP_TYPE_ABORT ; 
 int /*<<< orphan*/  IB_MGMT_RMPP_VERSION ; 
 scalar_t__ IS_ERR (struct ib_mad_send_buf*) ; 
 int /*<<< orphan*/  RDMA_DESTROY_AH_SLEEPABLE ; 
 struct ib_mad_send_buf* alloc_response_msg (int /*<<< orphan*/ *,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  ib_free_send_mad (struct ib_mad_send_buf*) ; 
 int ib_post_send_mad (struct ib_mad_send_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_set_rmpp_flags (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ib_rmpp_mad*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_ah (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nack_recv(struct ib_mad_agent_private *agent,
		      struct ib_mad_recv_wc *recv_wc, u8 rmpp_status)
{
	struct ib_mad_send_buf *msg;
	struct ib_rmpp_mad *rmpp_mad;
	int ret;

	msg = alloc_response_msg(&agent->agent, recv_wc);
	if (IS_ERR(msg))
		return;

	rmpp_mad = msg->mad;
	memcpy(rmpp_mad, recv_wc->recv_buf.mad, msg->hdr_len);

	rmpp_mad->mad_hdr.method ^= IB_MGMT_METHOD_RESP;
	rmpp_mad->rmpp_hdr.rmpp_version = IB_MGMT_RMPP_VERSION;
	rmpp_mad->rmpp_hdr.rmpp_type = IB_MGMT_RMPP_TYPE_ABORT;
	ib_set_rmpp_flags(&rmpp_mad->rmpp_hdr, IB_MGMT_RMPP_FLAG_ACTIVE);
	rmpp_mad->rmpp_hdr.rmpp_status = rmpp_status;
	rmpp_mad->rmpp_hdr.seg_num = 0;
	rmpp_mad->rmpp_hdr.paylen_newwin = 0;

	ret = ib_post_send_mad(msg, NULL);
	if (ret) {
		rdma_destroy_ah(msg->ah, RDMA_DESTROY_AH_SLEEPABLE);
		ib_free_send_mad(msg);
	}
}