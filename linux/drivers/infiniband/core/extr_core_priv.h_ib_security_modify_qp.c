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
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  real_qp; TYPE_2__* device; } ;
struct TYPE_3__ {int (* modify_qp ) (int /*<<< orphan*/ ,struct ib_qp_attr*,int,struct ib_udata*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct ib_qp_attr*,int,struct ib_udata*) ; 

__attribute__((used)) static inline int ib_security_modify_qp(struct ib_qp *qp,
					struct ib_qp_attr *qp_attr,
					int qp_attr_mask,
					struct ib_udata *udata)
{
	return qp->device->ops.modify_qp(qp->real_qp,
					 qp_attr,
					 qp_attr_mask,
					 udata);
}