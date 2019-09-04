#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xen_drm_front_info {int /*<<< orphan*/  xb_dev; } ;
struct TYPE_5__ {scalar_t__ sring; } ;
struct TYPE_7__ {int /*<<< orphan*/  completion; int /*<<< orphan*/  resp_status; TYPE_1__ ring; } ;
struct TYPE_6__ {scalar_t__ page; } ;
struct TYPE_8__ {TYPE_3__ req; TYPE_2__ evt; } ;
struct xen_drm_front_evtchnl {scalar_t__ type; scalar_t__ gref; scalar_t__ port; scalar_t__ irq; TYPE_4__ u; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EVTCHNL_STATE_DISCONNECTED ; 
 scalar_t__ EVTCHNL_TYPE_EVT ; 
 scalar_t__ EVTCHNL_TYPE_REQ ; 
 scalar_t__ GRANT_INVALID_REF ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access (scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  memset (struct xen_drm_front_evtchnl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (scalar_t__,struct xen_drm_front_evtchnl*) ; 
 int /*<<< orphan*/  xenbus_free_evtchn (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void evtchnl_free(struct xen_drm_front_info *front_info,
			 struct xen_drm_front_evtchnl *evtchnl)
{
	unsigned long page = 0;

	if (evtchnl->type == EVTCHNL_TYPE_REQ)
		page = (unsigned long)evtchnl->u.req.ring.sring;
	else if (evtchnl->type == EVTCHNL_TYPE_EVT)
		page = (unsigned long)evtchnl->u.evt.page;
	if (!page)
		return;

	evtchnl->state = EVTCHNL_STATE_DISCONNECTED;

	if (evtchnl->type == EVTCHNL_TYPE_REQ) {
		/* release all who still waits for response if any */
		evtchnl->u.req.resp_status = -EIO;
		complete_all(&evtchnl->u.req.completion);
	}

	if (evtchnl->irq)
		unbind_from_irqhandler(evtchnl->irq, evtchnl);

	if (evtchnl->port)
		xenbus_free_evtchn(front_info->xb_dev, evtchnl->port);

	/* end access and free the page */
	if (evtchnl->gref != GRANT_INVALID_REF)
		gnttab_end_foreign_access(evtchnl->gref, 0, page);

	memset(evtchnl, 0, sizeof(*evtchnl));
}