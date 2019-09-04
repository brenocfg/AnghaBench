#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iw_cm_event {int /*<<< orphan*/  status; int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  history; TYPE_1__* cm_id; } ;
struct c4iw_ep {TYPE_3__ com; int /*<<< orphan*/  hwtid; } ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_4__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*,struct iw_cm_event*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_UPCALL ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  IW_CM_EVENT_CLOSE ; 
 int /*<<< orphan*/  deref_cm_id (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (struct iw_cm_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct iw_cm_event*) ; 

__attribute__((used)) static void peer_abort_upcall(struct c4iw_ep *ep)
{
	struct iw_cm_event event;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	memset(&event, 0, sizeof(event));
	event.event = IW_CM_EVENT_CLOSE;
	event.status = -ECONNRESET;
	if (ep->com.cm_id) {
		pr_debug("abort delivered ep %p cm_id %p tid %u\n", ep,
			 ep->com.cm_id, ep->hwtid);
		ep->com.cm_id->event_handler(ep->com.cm_id, &event);
		deref_cm_id(&ep->com);
		set_bit(ABORT_UPCALL, &ep->com.history);
	}
}