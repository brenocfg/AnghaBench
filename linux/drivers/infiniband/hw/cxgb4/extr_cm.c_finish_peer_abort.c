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
struct c4iw_qp_attributes {int /*<<< orphan*/  next_state; } ;
struct TYPE_3__ {TYPE_2__* qp; scalar_t__ cm_id; } ;
struct c4iw_ep {TYPE_1__ com; int /*<<< orphan*/  srqe_idx; } ;
struct c4iw_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rhp; } ;

/* Variables and functions */
 int /*<<< orphan*/  C4IW_QP_ATTR_NEXT_STATE ; 
 int /*<<< orphan*/  C4IW_QP_STATE_ERROR ; 
 int /*<<< orphan*/  c4iw_modify_qp (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,struct c4iw_qp_attributes*,int) ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_1__*) ; 
 int /*<<< orphan*/  complete_cached_srq_buffers (struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peer_abort_upcall (struct c4iw_ep*) ; 
 int /*<<< orphan*/  release_ep_resources (struct c4iw_ep*) ; 

__attribute__((used)) static void finish_peer_abort(struct c4iw_dev *dev, struct c4iw_ep *ep)
{
	complete_cached_srq_buffers(ep, ep->srqe_idx);
	if (ep->com.cm_id && ep->com.qp) {
		struct c4iw_qp_attributes attrs;

		attrs.next_state = C4IW_QP_STATE_ERROR;
		c4iw_modify_qp(ep->com.qp->rhp, ep->com.qp,
			       C4IW_QP_ATTR_NEXT_STATE,	&attrs, 1);
	}
	peer_abort_upcall(ep);
	release_ep_resources(ep);
	c4iw_put_ep(&ep->com);
}