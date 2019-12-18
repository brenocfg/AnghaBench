#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rmpp_rtime_flags; scalar_t__ rmpp_version; int rmpp_type; } ;
struct ib_rmpp_mad {TYPE_2__ rmpp_hdr; } ;
struct TYPE_3__ {scalar_t__ mad; } ;
struct ib_mad_recv_wc {TYPE_1__ recv_buf; } ;
struct ib_mad_agent_private {int dummy; } ;

/* Variables and functions */
 int IB_MGMT_RMPP_FLAG_ACTIVE ; 
 int /*<<< orphan*/  IB_MGMT_RMPP_STATUS_BADT ; 
 int /*<<< orphan*/  IB_MGMT_RMPP_STATUS_UNV ; 
#define  IB_MGMT_RMPP_TYPE_ABORT 131 
#define  IB_MGMT_RMPP_TYPE_ACK 130 
#define  IB_MGMT_RMPP_TYPE_DATA 129 
#define  IB_MGMT_RMPP_TYPE_STOP 128 
 scalar_t__ IB_MGMT_RMPP_VERSION ; 
 int /*<<< orphan*/  abort_send (struct ib_mad_agent_private*,struct ib_mad_recv_wc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_free_recv_mad (struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  nack_recv (struct ib_mad_agent_private*,struct ib_mad_recv_wc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_rmpp_abort (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  process_rmpp_ack (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 struct ib_mad_recv_wc* process_rmpp_data (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  process_rmpp_stop (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 

struct ib_mad_recv_wc *
ib_process_rmpp_recv_wc(struct ib_mad_agent_private *agent,
			struct ib_mad_recv_wc *mad_recv_wc)
{
	struct ib_rmpp_mad *rmpp_mad;

	rmpp_mad = (struct ib_rmpp_mad *)mad_recv_wc->recv_buf.mad;
	if (!(rmpp_mad->rmpp_hdr.rmpp_rtime_flags & IB_MGMT_RMPP_FLAG_ACTIVE))
		return mad_recv_wc;

	if (rmpp_mad->rmpp_hdr.rmpp_version != IB_MGMT_RMPP_VERSION) {
		abort_send(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_UNV);
		nack_recv(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_UNV);
		goto out;
	}

	switch (rmpp_mad->rmpp_hdr.rmpp_type) {
	case IB_MGMT_RMPP_TYPE_DATA:
		return process_rmpp_data(agent, mad_recv_wc);
	case IB_MGMT_RMPP_TYPE_ACK:
		process_rmpp_ack(agent, mad_recv_wc);
		break;
	case IB_MGMT_RMPP_TYPE_STOP:
		process_rmpp_stop(agent, mad_recv_wc);
		break;
	case IB_MGMT_RMPP_TYPE_ABORT:
		process_rmpp_abort(agent, mad_recv_wc);
		break;
	default:
		abort_send(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_BADT);
		nack_recv(agent, mad_recv_wc, IB_MGMT_RMPP_STATUS_BADT);
		break;
	}
out:
	ib_free_recv_mad(mad_recv_wc);
	return NULL;
}