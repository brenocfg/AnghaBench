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
struct TYPE_4__ {scalar_t__ req_cons; TYPE_1__* sring; } ;
struct xenvif {TYPE_2__ ctrl; } ;
struct xen_netif_ctrl_request {int dummy; } ;
struct TYPE_3__ {scalar_t__ req_prod; scalar_t__ req_event; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  RING_COPY_REQUEST (TYPE_2__*,scalar_t__,struct xen_netif_ctrl_request*) ; 
 int /*<<< orphan*/  process_ctrl_request (struct xenvif*,struct xen_netif_ctrl_request*) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static void xenvif_ctrl_action(struct xenvif *vif)
{
	for (;;) {
		RING_IDX req_prod, req_cons;

		req_prod = vif->ctrl.sring->req_prod;
		req_cons = vif->ctrl.req_cons;

		/* Make sure we can see requests before we process them. */
		rmb();

		if (req_cons == req_prod)
			break;

		while (req_cons != req_prod) {
			struct xen_netif_ctrl_request req;

			RING_COPY_REQUEST(&vif->ctrl, req_cons, &req);
			req_cons++;

			process_ctrl_request(vif, &req);
		}

		vif->ctrl.req_cons = req_cons;
		vif->ctrl.sring->req_event = req_cons + 1;
	}
}