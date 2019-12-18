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
union ib_gid {scalar_t__ raw; } ;
typedef  int /*<<< orphan*/  u16 ;
struct in6_addr {int dummy; } ;
struct ib_qp {scalar_t__ qp_type; int /*<<< orphan*/  usecnt; TYPE_2__* device; } ;
struct TYPE_3__ {int (* attach_mcast ) (struct ib_qp*,union ib_gid*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IB_QPT_UD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_mcast_lid (struct ib_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_is_multicast_addr (struct in6_addr*) ; 
 int stub1 (struct ib_qp*,union ib_gid*,int /*<<< orphan*/ ) ; 

int ib_attach_mcast(struct ib_qp *qp, union ib_gid *gid, u16 lid)
{
	int ret;

	if (!qp->device->ops.attach_mcast)
		return -EOPNOTSUPP;

	if (!rdma_is_multicast_addr((struct in6_addr *)gid->raw) ||
	    qp->qp_type != IB_QPT_UD || !is_valid_mcast_lid(qp, lid))
		return -EINVAL;

	ret = qp->device->ops.attach_mcast(qp, gid, lid);
	if (!ret)
		atomic_inc(&qp->usecnt);
	return ret;
}