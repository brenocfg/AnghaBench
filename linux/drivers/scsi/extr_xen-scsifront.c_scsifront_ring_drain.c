#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vscsiif_response {int dummy; } ;
struct TYPE_5__ {scalar_t__ rsp_cons; scalar_t__ req_prod_pvt; TYPE_1__* sring; } ;
struct vscsifrnt_info {TYPE_2__ ring; } ;
struct TYPE_4__ {scalar_t__ rsp_prod; scalar_t__ rsp_event; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  RING_FINAL_CHECK_FOR_RESPONSES (TYPE_2__*,int) ; 
 struct vscsiif_response* RING_GET_RESPONSE (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  scsifront_do_response (struct vscsifrnt_info*,struct vscsiif_response*) ; 

__attribute__((used)) static int scsifront_ring_drain(struct vscsifrnt_info *info)
{
	struct vscsiif_response *ring_rsp;
	RING_IDX i, rp;
	int more_to_do = 0;

	rp = info->ring.sring->rsp_prod;
	rmb();	/* ordering required respective to dom0 */
	for (i = info->ring.rsp_cons; i != rp; i++) {
		ring_rsp = RING_GET_RESPONSE(&info->ring, i);
		scsifront_do_response(info, ring_rsp);
	}

	info->ring.rsp_cons = i;

	if (i != info->ring.req_prod_pvt)
		RING_FINAL_CHECK_FOR_RESPONSES(&info->ring, more_to_do);
	else
		info->ring.sring->rsp_event = i + 1;

	return more_to_do;
}