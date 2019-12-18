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
struct qedr_iw_ep {TYPE_2__* cm_id; } ;
struct qed_iwarp_cm_event_params {TYPE_1__* cm_info; int /*<<< orphan*/  status; } ;
struct iw_cm_event {int event; void* private_data; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  ord; int /*<<< orphan*/  ird; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  event ;
typedef  enum iw_cm_event_type { ____Placeholder_iw_cm_event_type } iw_cm_event_type ;
struct TYPE_4__ {int /*<<< orphan*/  (* event_handler ) (TYPE_2__*,struct iw_cm_event*) ;} ;
struct TYPE_3__ {scalar_t__ private_data; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  ord; int /*<<< orphan*/  ird; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct iw_cm_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct iw_cm_event*) ; 

__attribute__((used)) static void
qedr_iw_issue_event(void *context,
		    struct qed_iwarp_cm_event_params *params,
		    enum iw_cm_event_type event_type)
{
	struct qedr_iw_ep *ep = (struct qedr_iw_ep *)context;
	struct iw_cm_event event;

	memset(&event, 0, sizeof(event));
	event.status = params->status;
	event.event = event_type;

	if (params->cm_info) {
		event.ird = params->cm_info->ird;
		event.ord = params->cm_info->ord;
		event.private_data_len = params->cm_info->private_data_len;
		event.private_data = (void *)params->cm_info->private_data;
	}

	if (ep->cm_id)
		ep->cm_id->event_handler(ep->cm_id, &event);
}