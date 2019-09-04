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
typedef  scalar_t__ u8 ;
struct qed_iwarp_ep {scalar_t__ connect_mode; int /*<<< orphan*/ * syn; } ;
struct qed_hwfn {TYPE_2__* p_rdma_info; } ;
struct TYPE_3__ {scalar_t__ ll2_syn_handle; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 scalar_t__ RDMA_RETURN_OK ; 
 scalar_t__ TCP_CONNECT_PASSIVE ; 
 int /*<<< orphan*/  qed_iwarp_ll2_post_rx (struct qed_hwfn*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  qed_iwarp_mpa_offload (struct qed_hwfn*,struct qed_iwarp_ep*) ; 
 int /*<<< orphan*/  qed_iwarp_mpa_received (struct qed_hwfn*,struct qed_iwarp_ep*) ; 
 int /*<<< orphan*/  qed_iwarp_tcp_connect_unsuccessful (struct qed_hwfn*,struct qed_iwarp_ep*,scalar_t__) ; 

__attribute__((used)) static void
qed_iwarp_connect_complete(struct qed_hwfn *p_hwfn,
			   struct qed_iwarp_ep *ep, u8 fw_return_code)
{
	u8 ll2_syn_handle = p_hwfn->p_rdma_info->iwarp.ll2_syn_handle;

	if (ep->connect_mode == TCP_CONNECT_PASSIVE) {
		/* Done with the SYN packet, post back to ll2 rx */
		qed_iwarp_ll2_post_rx(p_hwfn, ep->syn, ll2_syn_handle);

		ep->syn = NULL;

		/* If connect failed - upper layer doesn't know about it */
		if (fw_return_code == RDMA_RETURN_OK)
			qed_iwarp_mpa_received(p_hwfn, ep);
		else
			qed_iwarp_tcp_connect_unsuccessful(p_hwfn, ep,
							   fw_return_code);
	} else {
		if (fw_return_code == RDMA_RETURN_OK)
			qed_iwarp_mpa_offload(p_hwfn, ep);
		else
			qed_iwarp_tcp_connect_unsuccessful(p_hwfn, ep,
							   fw_return_code);
	}
}