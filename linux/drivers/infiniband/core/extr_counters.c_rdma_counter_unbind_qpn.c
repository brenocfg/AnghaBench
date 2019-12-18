#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_6__ {scalar_t__ mode; } ;
struct rdma_port_counter {TYPE_3__ mode; } ;
struct ib_qp {scalar_t__ port; int /*<<< orphan*/  res; TYPE_2__* counter; } ;
struct ib_device {TYPE_1__* port_data; } ;
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_4__ {struct rdma_port_counter port_counter; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ RDMA_COUNTER_MODE_MANUAL ; 
 struct ib_qp* rdma_counter_get_qp (struct ib_device*,scalar_t__) ; 
 int rdma_counter_unbind_qp (struct ib_qp*,int) ; 
 scalar_t__ rdma_is_port_valid (struct ib_device*,scalar_t__) ; 
 int /*<<< orphan*/  rdma_restrack_put (int /*<<< orphan*/ *) ; 

int rdma_counter_unbind_qpn(struct ib_device *dev, u8 port,
			    u32 qp_num, u32 counter_id)
{
	struct rdma_port_counter *port_counter;
	struct ib_qp *qp;
	int ret;

	if (!rdma_is_port_valid(dev, port))
		return -EINVAL;

	qp = rdma_counter_get_qp(dev, qp_num);
	if (!qp)
		return -ENOENT;

	if (rdma_is_port_valid(dev, qp->port) && (qp->port != port)) {
		ret = -EINVAL;
		goto out;
	}

	port_counter = &dev->port_data[port].port_counter;
	if (!qp->counter || qp->counter->id != counter_id ||
	    port_counter->mode.mode != RDMA_COUNTER_MODE_MANUAL) {
		ret = -EINVAL;
		goto out;
	}

	ret = rdma_counter_unbind_qp(qp, false);

out:
	rdma_restrack_put(&qp->res);
	return ret;
}