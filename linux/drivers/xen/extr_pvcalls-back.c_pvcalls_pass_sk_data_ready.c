#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_1__ poll; } ;
struct xen_pvcalls_response {scalar_t__ cmd; scalar_t__ ret; TYPE_2__ u; int /*<<< orphan*/  req_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_3__ poll; } ;
struct TYPE_12__ {scalar_t__ cmd; TYPE_4__ u; int /*<<< orphan*/  req_id; } ;
struct sockpass_mapping {int /*<<< orphan*/  register_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  copy_lock; struct pvcalls_fedata* fedata; TYPE_5__ reqcopy; } ;
struct sock {struct sockpass_mapping* sk_user_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  rsp_prod_pvt; } ;
struct pvcalls_fedata {int /*<<< orphan*/  irq; TYPE_6__ ring; } ;

/* Variables and functions */
 scalar_t__ PVCALLS_POLL ; 
 struct xen_pvcalls_response* RING_GET_RESPONSE (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_PUSH_RESPONSES_AND_CHECK_NOTIFY (TYPE_6__*,int) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pvcalls_pass_sk_data_ready(struct sock *sock)
{
	struct sockpass_mapping *mappass = sock->sk_user_data;
	struct pvcalls_fedata *fedata;
	struct xen_pvcalls_response *rsp;
	unsigned long flags;
	int notify;

	if (mappass == NULL)
		return;

	fedata = mappass->fedata;
	spin_lock_irqsave(&mappass->copy_lock, flags);
	if (mappass->reqcopy.cmd == PVCALLS_POLL) {
		rsp = RING_GET_RESPONSE(&fedata->ring,
					fedata->ring.rsp_prod_pvt++);
		rsp->req_id = mappass->reqcopy.req_id;
		rsp->u.poll.id = mappass->reqcopy.u.poll.id;
		rsp->cmd = mappass->reqcopy.cmd;
		rsp->ret = 0;

		mappass->reqcopy.cmd = 0;
		spin_unlock_irqrestore(&mappass->copy_lock, flags);

		RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&fedata->ring, notify);
		if (notify)
			notify_remote_via_irq(mappass->fedata->irq);
	} else {
		spin_unlock_irqrestore(&mappass->copy_lock, flags);
		queue_work(mappass->wq, &mappass->register_work);
	}
}