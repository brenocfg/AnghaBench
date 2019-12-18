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
struct ib_cq {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct siw_cq {struct ib_cq base_cq; } ;
struct TYPE_2__ {struct ib_cq* cq; } ;
struct ib_event {int event; TYPE_1__ element; int /*<<< orphan*/  device; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  siw_dbg_cq (struct siw_cq*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

void siw_cq_event(struct siw_cq *cq, enum ib_event_type etype)
{
	struct ib_event event;
	struct ib_cq *base_cq = &cq->base_cq;

	event.event = etype;
	event.device = base_cq->device;
	event.element.cq = base_cq;

	if (base_cq->event_handler) {
		siw_dbg_cq(cq, "reporting CQ event %d\n", etype);
		base_cq->event_handler(&event, base_cq->cq_context);
	}
}