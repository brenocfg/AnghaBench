#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ib_qp_init_attr {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * sgid_attr; } ;
struct TYPE_10__ {TYPE_3__ grh; } ;
struct TYPE_7__ {int /*<<< orphan*/ * sgid_attr; } ;
struct TYPE_8__ {TYPE_1__ grh; } ;
struct ib_qp_attr {TYPE_4__ alt_ah_attr; TYPE_2__ ah_attr; } ;
struct ib_qp {int /*<<< orphan*/  real_qp; TYPE_6__* device; } ;
struct TYPE_11__ {int (* query_qp ) (int /*<<< orphan*/ ,struct ib_qp_attr*,int,struct ib_qp_init_attr*) ;} ;
struct TYPE_12__ {TYPE_5__ ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (int /*<<< orphan*/ ,struct ib_qp_attr*,int,struct ib_qp_init_attr*) ; 

int ib_query_qp(struct ib_qp *qp,
		struct ib_qp_attr *qp_attr,
		int qp_attr_mask,
		struct ib_qp_init_attr *qp_init_attr)
{
	qp_attr->ah_attr.grh.sgid_attr = NULL;
	qp_attr->alt_ah_attr.grh.sgid_attr = NULL;

	return qp->device->ops.query_qp ?
		qp->device->ops.query_qp(qp->real_qp, qp_attr, qp_attr_mask,
					 qp_init_attr) : -EOPNOTSUPP;
}