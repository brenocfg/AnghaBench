#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct xendispl_req {scalar_t__ id; int /*<<< orphan*/  operation; } ;
struct TYPE_6__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct TYPE_4__ {TYPE_3__ ring; } ;
struct TYPE_5__ {TYPE_1__ req; } ;
struct xen_drm_front_evtchnl {scalar_t__ evt_id; int /*<<< orphan*/  evt_next_id; TYPE_2__ u; } ;

/* Variables and functions */
 struct xendispl_req* RING_GET_REQUEST (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xendispl_req *
be_prepare_req(struct xen_drm_front_evtchnl *evtchnl, u8 operation)
{
	struct xendispl_req *req;

	req = RING_GET_REQUEST(&evtchnl->u.req.ring,
			       evtchnl->u.req.ring.req_prod_pvt);
	req->operation = operation;
	req->id = evtchnl->evt_next_id++;
	evtchnl->evt_id = req->id;
	return req;
}