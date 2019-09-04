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
typedef  int u8 ;
struct qed_iwarp_reject_in {int private_data_len; int /*<<< orphan*/  private_data; int /*<<< orphan*/  cb_context; struct qed_iwarp_ep* ep_context; } ;
struct TYPE_3__ {int private_data_len; scalar_t__ private_data; } ;
struct qed_iwarp_ep {TYPE_2__* ep_buffer_virt; TYPE_1__ cm_info; int /*<<< orphan*/ * qp; int /*<<< orphan*/  cb_context; int /*<<< orphan*/  tcp_cid; } ;
struct qed_hwfn {int dummy; } ;
struct TYPE_4__ {scalar_t__ out_pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int qed_iwarp_mpa_offload (struct qed_hwfn*,struct qed_iwarp_ep*) ; 
 int /*<<< orphan*/  qed_iwarp_mpa_v2_set_private (struct qed_hwfn*,struct qed_iwarp_ep*,int*) ; 

int qed_iwarp_reject(void *rdma_cxt, struct qed_iwarp_reject_in *iparams)
{
	struct qed_hwfn *p_hwfn = rdma_cxt;
	struct qed_iwarp_ep *ep;
	u8 mpa_data_size = 0;

	ep = iparams->ep_context;
	if (!ep) {
		DP_ERR(p_hwfn, "Ep Context receive in reject is NULL\n");
		return -EINVAL;
	}

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "EP(0x%x)\n", ep->tcp_cid);

	ep->cb_context = iparams->cb_context;
	ep->qp = NULL;

	qed_iwarp_mpa_v2_set_private(p_hwfn, ep, &mpa_data_size);

	ep->cm_info.private_data = ep->ep_buffer_virt->out_pdata;
	ep->cm_info.private_data_len = iparams->private_data_len +
				       mpa_data_size;

	memcpy((u8 *)ep->ep_buffer_virt->out_pdata + mpa_data_size,
	       iparams->private_data, iparams->private_data_len);

	return qed_iwarp_mpa_offload(p_hwfn, ep);
}