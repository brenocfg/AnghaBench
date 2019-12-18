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
struct qedr_iw_ep {struct qedr_dev* dev; } ;
struct qedr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_1__* ops; } ;
struct qed_iwarp_send_rtr_in {int /*<<< orphan*/  ep_context; } ;
struct qed_iwarp_cm_event_params {int /*<<< orphan*/  ep_context; } ;
struct TYPE_2__ {int (* iwarp_send_rtr ) (int /*<<< orphan*/ ,struct qed_iwarp_send_rtr_in*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct qed_iwarp_send_rtr_in*) ; 

__attribute__((used)) static int
qedr_iw_mpa_reply(void *context, struct qed_iwarp_cm_event_params *params)
{
	struct qedr_iw_ep *ep = (struct qedr_iw_ep *)context;
	struct qedr_dev *dev = ep->dev;
	struct qed_iwarp_send_rtr_in rtr_in;

	rtr_in.ep_context = params->ep_context;

	return dev->ops->iwarp_send_rtr(dev->rdma_ctx, &rtr_in);
}