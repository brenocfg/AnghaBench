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
struct TYPE_2__ {int /*<<< orphan*/  ird; int /*<<< orphan*/  ord; } ;
struct qed_iwarp_ep {scalar_t__ connect_mode; int mpa_reply_processed; int /*<<< orphan*/  cb_context; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,struct qed_iwarp_cm_event_params*) ;TYPE_1__ cm_info; int /*<<< orphan*/  mpa_rev; } ;
struct qed_iwarp_cm_event_params {scalar_t__ status; struct qed_iwarp_ep* ep_context; TYPE_1__* cm_info; int /*<<< orphan*/  event; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_IWARP_EVENT_ACTIVE_MPA_REPLY ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 scalar_t__ TCP_CONNECT_PASSIVE ; 
 int /*<<< orphan*/  qed_iwarp_parse_private_data (struct qed_hwfn*,struct qed_iwarp_ep*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_iwarp_cm_event_params*) ; 

__attribute__((used)) static void
qed_iwarp_mpa_reply_arrived(struct qed_hwfn *p_hwfn, struct qed_iwarp_ep *ep)
{
	struct qed_iwarp_cm_event_params params;

	if (ep->connect_mode == TCP_CONNECT_PASSIVE) {
		DP_NOTICE(p_hwfn,
			  "MPA reply event not expected on passive side!\n");
		return;
	}

	params.event = QED_IWARP_EVENT_ACTIVE_MPA_REPLY;

	qed_iwarp_parse_private_data(p_hwfn, ep);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "MPA_NEGOTIATE (v%d): ORD: 0x%x IRD: 0x%x\n",
		   ep->mpa_rev, ep->cm_info.ord, ep->cm_info.ird);

	params.cm_info = &ep->cm_info;
	params.ep_context = ep;
	params.status = 0;

	ep->mpa_reply_processed = true;

	ep->event_cb(ep->cb_context, &params);
}