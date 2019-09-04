#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ib_wc {int dummy; } ;
struct ib_smp {int dummy; } ;
struct ib_mad_qp_info {TYPE_4__* qp; } ;
struct TYPE_8__ {int /*<<< orphan*/ * grh; struct ib_mad* mad; } ;
struct TYPE_9__ {TYPE_1__ recv_buf; int /*<<< orphan*/ * wc; } ;
struct TYPE_10__ {TYPE_2__ recv_wc; int /*<<< orphan*/  wc; } ;
struct ib_mad_private {int /*<<< orphan*/  mad_size; int /*<<< orphan*/  grh; scalar_t__ mad; TYPE_3__ header; } ;
struct ib_mad_port_private {TYPE_5__* device; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_mad {int dummy; } ;
typedef  enum smi_forward_action { ____Placeholder_smi_forward_action } smi_forward_action ;
typedef  enum smi_action { ____Placeholder_smi_action } smi_action ;
struct TYPE_12__ {int /*<<< orphan*/  phys_port_cnt; } ;
struct TYPE_11__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 scalar_t__ IB_SMI_DISCARD ; 
 int IB_SMI_HANDLE ; 
 int IB_SMI_LOCAL ; 
 int IB_SMI_SEND ; 
 int /*<<< orphan*/  agent_send_response (struct ib_mad_hdr const*,int /*<<< orphan*/ *,struct ib_wc const*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mad_priv_size (struct ib_mad_private*) ; 
 int /*<<< orphan*/  memcpy (struct ib_mad_private*,struct ib_mad_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_cap_ib_switch (TYPE_5__*) ; 
 int smi_check_forward_dr_smp (struct ib_smp*) ; 
 scalar_t__ smi_check_local_smp (struct ib_smp*,TYPE_5__*) ; 
 int /*<<< orphan*/  smi_get_fwd_port (struct ib_smp*) ; 
 scalar_t__ smi_handle_dr_smp_recv (struct ib_smp*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ smi_handle_dr_smp_send (struct ib_smp*,scalar_t__,int) ; 

__attribute__((used)) static enum smi_action handle_ib_smi(const struct ib_mad_port_private *port_priv,
				     const struct ib_mad_qp_info *qp_info,
				     const struct ib_wc *wc,
				     int port_num,
				     struct ib_mad_private *recv,
				     struct ib_mad_private *response)
{
	enum smi_forward_action retsmi;
	struct ib_smp *smp = (struct ib_smp *)recv->mad;

	if (smi_handle_dr_smp_recv(smp,
				   rdma_cap_ib_switch(port_priv->device),
				   port_num,
				   port_priv->device->phys_port_cnt) ==
				   IB_SMI_DISCARD)
		return IB_SMI_DISCARD;

	retsmi = smi_check_forward_dr_smp(smp);
	if (retsmi == IB_SMI_LOCAL)
		return IB_SMI_HANDLE;

	if (retsmi == IB_SMI_SEND) { /* don't forward */
		if (smi_handle_dr_smp_send(smp,
					   rdma_cap_ib_switch(port_priv->device),
					   port_num) == IB_SMI_DISCARD)
			return IB_SMI_DISCARD;

		if (smi_check_local_smp(smp, port_priv->device) == IB_SMI_DISCARD)
			return IB_SMI_DISCARD;
	} else if (rdma_cap_ib_switch(port_priv->device)) {
		/* forward case for switches */
		memcpy(response, recv, mad_priv_size(response));
		response->header.recv_wc.wc = &response->header.wc;
		response->header.recv_wc.recv_buf.mad = (struct ib_mad *)response->mad;
		response->header.recv_wc.recv_buf.grh = &response->grh;

		agent_send_response((const struct ib_mad_hdr *)response->mad,
				    &response->grh, wc,
				    port_priv->device,
				    smi_get_fwd_port(smp),
				    qp_info->qp->qp_num,
				    response->mad_size,
				    false);

		return IB_SMI_DISCARD;
	}
	return IB_SMI_HANDLE;
}