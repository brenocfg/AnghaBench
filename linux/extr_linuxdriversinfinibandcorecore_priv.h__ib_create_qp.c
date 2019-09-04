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
struct ib_uobject {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_init_attr {scalar_t__ qp_type; } ;
struct TYPE_2__ {int valid; int /*<<< orphan*/  type; } ;
struct ib_qp {TYPE_1__ res; struct ib_uobject* uobject; struct ib_pd* pd; struct ib_device* device; } ;
struct ib_pd {int dummy; } ;
struct ib_device {struct ib_qp* (* create_qp ) (struct ib_pd*,struct ib_qp_init_attr*,struct ib_udata*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct ib_qp* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IB_QPT_XRC_INI ; 
 scalar_t__ IS_ERR (struct ib_qp*) ; 
 int /*<<< orphan*/  RDMA_RESTRACK_QP ; 
 int /*<<< orphan*/  rdma_restrack_add (TYPE_1__*) ; 
 struct ib_qp* stub1 (struct ib_pd*,struct ib_qp_init_attr*,struct ib_udata*) ; 

__attribute__((used)) static inline struct ib_qp *_ib_create_qp(struct ib_device *dev,
					  struct ib_pd *pd,
					  struct ib_qp_init_attr *attr,
					  struct ib_udata *udata,
					  struct ib_uobject *uobj)
{
	struct ib_qp *qp;

	if (!dev->create_qp)
		return ERR_PTR(-EOPNOTSUPP);

	qp = dev->create_qp(pd, attr, udata);
	if (IS_ERR(qp))
		return qp;

	qp->device = dev;
	qp->pd = pd;
	qp->uobject = uobj;
	/*
	 * We don't track XRC QPs for now, because they don't have PD
	 * and more importantly they are created internaly by driver,
	 * see mlx5 create_dev_resources() as an example.
	 */
	if (attr->qp_type < IB_QPT_XRC_INI) {
		qp->res.type = RDMA_RESTRACK_QP;
		rdma_restrack_add(&qp->res);
	} else
		qp->res.valid = false;

	return qp;
}