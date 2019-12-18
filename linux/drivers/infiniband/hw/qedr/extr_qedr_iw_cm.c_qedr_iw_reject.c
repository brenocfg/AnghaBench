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
typedef  int /*<<< orphan*/  u8 ;
struct qedr_iw_ep {int /*<<< orphan*/ * qp; int /*<<< orphan*/  qed_context; struct qedr_dev* dev; } ;
struct qedr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_1__* ops; } ;
struct qed_iwarp_reject_in {int /*<<< orphan*/  private_data_len; void const* private_data; struct qedr_iw_ep* cb_context; int /*<<< orphan*/  ep_context; } ;
struct iw_cm_id {scalar_t__ provider_data; } ;
struct TYPE_2__ {int (* iwarp_reject ) (int /*<<< orphan*/ ,struct qed_iwarp_reject_in*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct qed_iwarp_reject_in*) ; 

int qedr_iw_reject(struct iw_cm_id *cm_id, const void *pdata, u8 pdata_len)
{
	struct qedr_iw_ep *ep = (struct qedr_iw_ep *)cm_id->provider_data;
	struct qedr_dev *dev = ep->dev;
	struct qed_iwarp_reject_in params;

	params.ep_context = ep->qed_context;
	params.cb_context = ep;
	params.private_data = pdata;
	params.private_data_len = pdata_len;
	ep->qp = NULL;

	return dev->ops->iwarp_reject(dev->rdma_ctx, &params);
}