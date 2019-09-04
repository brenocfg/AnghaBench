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
struct qedr_iw_ep {TYPE_1__* cm_id; } ;
struct qed_iwarp_cm_event_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rem_ref ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IW_CM_EVENT_CLOSE ; 
 int /*<<< orphan*/  qedr_iw_issue_event (void*,struct qed_iwarp_cm_event_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
qedr_iw_close_event(void *context, struct qed_iwarp_cm_event_params *params)
{
	struct qedr_iw_ep *ep = (struct qedr_iw_ep *)context;

	if (ep->cm_id) {
		qedr_iw_issue_event(context, params, IW_CM_EVENT_CLOSE);

		ep->cm_id->rem_ref(ep->cm_id);
		ep->cm_id = NULL;
	}
}