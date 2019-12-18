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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ rsp_prod_pvt; } ;
struct xenvif {TYPE_1__ ctrl; } ;
struct xen_netif_ctrl_response {int /*<<< orphan*/  data; int /*<<< orphan*/  status; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct xen_netif_ctrl_request {int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 struct xen_netif_ctrl_response* RING_GET_RESPONSE (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void make_ctrl_response(struct xenvif *vif,
			       const struct xen_netif_ctrl_request *req,
			       u32 status, u32 data)
{
	RING_IDX idx = vif->ctrl.rsp_prod_pvt;
	struct xen_netif_ctrl_response rsp = {
		.id = req->id,
		.type = req->type,
		.status = status,
		.data = data,
	};

	*RING_GET_RESPONSE(&vif->ctrl, idx) = rsp;
	vif->ctrl.rsp_prod_pvt = ++idx;
}