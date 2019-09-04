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
struct qedr_iw_ep {int /*<<< orphan*/  qp; struct qedr_dev* dev; } ;
struct qedr_dev {int dummy; } ;
struct qed_iwarp_cm_event_params {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ECONNREFUSED ; 
 int /*<<< orphan*/  IW_CM_EVENT_ESTABLISHED ; 
 int /*<<< orphan*/  QEDR_MSG_IWARP ; 
 int /*<<< orphan*/  kfree (struct qedr_iw_ep*) ; 
 int /*<<< orphan*/  qedr_iw_close_event (void*,struct qed_iwarp_cm_event_params*) ; 
 int /*<<< orphan*/  qedr_iw_issue_event (void*,struct qed_iwarp_cm_event_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qedr_iw_passive_complete(void *context,
			 struct qed_iwarp_cm_event_params *params)
{
	struct qedr_iw_ep *ep = (struct qedr_iw_ep *)context;
	struct qedr_dev *dev = ep->dev;

	/* We will only reach the following state if MPA_REJECT was called on
	 * passive. In this case there will be no associated QP.
	 */
	if ((params->status == -ECONNREFUSED) && (!ep->qp)) {
		DP_DEBUG(dev, QEDR_MSG_IWARP,
			 "PASSIVE connection refused releasing ep...\n");
		kfree(ep);
		return;
	}

	qedr_iw_issue_event(context, params, IW_CM_EVENT_ESTABLISHED);

	if (params->status < 0)
		qedr_iw_close_event(context, params);
}