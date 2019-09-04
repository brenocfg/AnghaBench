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
typedef  int /*<<< orphan*/  uresp ;
typedef  int /*<<< orphan*/  u16 ;
struct ib_pd {int dummy; } ;
struct qedr_pd {struct ib_pd ibpd; TYPE_2__* uctx; int /*<<< orphan*/  pd_id; } ;
struct qedr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_1__* ops; } ;
struct qedr_alloc_pd_uresp {int /*<<< orphan*/  pd_id; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {struct qedr_pd* pd; } ;
struct TYPE_3__ {int (* rdma_alloc_pd ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* rdma_dealloc_pd ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_pd* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QEDR_MSG_INIT ; 
 struct qedr_dev* get_qedr_dev (struct ib_device*) ; 
 TYPE_2__* get_qedr_ucontext (struct ib_ucontext*) ; 
 int /*<<< orphan*/  kfree (struct qedr_pd*) ; 
 struct qedr_pd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qedr_ib_copy_to_udata (struct ib_udata*,struct qedr_alloc_pd_uresp*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ib_pd *qedr_alloc_pd(struct ib_device *ibdev,
			    struct ib_ucontext *context, struct ib_udata *udata)
{
	struct qedr_dev *dev = get_qedr_dev(ibdev);
	struct qedr_pd *pd;
	u16 pd_id;
	int rc;

	DP_DEBUG(dev, QEDR_MSG_INIT, "Function called from: %s\n",
		 (udata && context) ? "User Lib" : "Kernel");

	if (!dev->rdma_ctx) {
		DP_ERR(dev, "invalid RDMA context\n");
		return ERR_PTR(-EINVAL);
	}

	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return ERR_PTR(-ENOMEM);

	rc = dev->ops->rdma_alloc_pd(dev->rdma_ctx, &pd_id);
	if (rc)
		goto err;

	pd->pd_id = pd_id;

	if (udata && context) {
		struct qedr_alloc_pd_uresp uresp = {
			.pd_id = pd_id,
		};

		rc = qedr_ib_copy_to_udata(udata, &uresp, sizeof(uresp));
		if (rc) {
			DP_ERR(dev, "copy error pd_id=0x%x.\n", pd_id);
			dev->ops->rdma_dealloc_pd(dev->rdma_ctx, pd_id);
			goto err;
		}

		pd->uctx = get_qedr_ucontext(context);
		pd->uctx->pd = pd;
	}

	return &pd->ibpd;

err:
	kfree(pd);
	return ERR_PTR(rc);
}