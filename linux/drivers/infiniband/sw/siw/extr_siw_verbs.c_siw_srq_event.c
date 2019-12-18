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
struct ib_srq {int /*<<< orphan*/  srq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pd; int /*<<< orphan*/  device; } ;
struct siw_srq {struct ib_srq base_srq; } ;
struct TYPE_2__ {struct ib_srq* srq; } ;
struct ib_event {int event; TYPE_1__ element; int /*<<< orphan*/  device; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  siw_dbg_pd (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

void siw_srq_event(struct siw_srq *srq, enum ib_event_type etype)
{
	struct ib_event event;
	struct ib_srq *base_srq = &srq->base_srq;

	event.event = etype;
	event.device = base_srq->device;
	event.element.srq = base_srq;

	if (base_srq->event_handler) {
		siw_dbg_pd(srq->base_srq.pd,
			   "reporting SRQ event %d\n", etype);
		base_srq->event_handler(&event, base_srq->srq_context);
	}
}