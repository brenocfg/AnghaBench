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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rdma_counter {int /*<<< orphan*/  id; } ;
struct ib_qp {size_t port; int /*<<< orphan*/  res; } ;
struct ib_device {TYPE_2__* port_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  hstats; } ;
struct TYPE_4__ {TYPE_1__ port_counter; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  RDMA_COUNTER_MODE_MANUAL ; 
 struct rdma_counter* rdma_counter_alloc (struct ib_device*,size_t,int /*<<< orphan*/ ) ; 
 int rdma_counter_bind_qp_manual (struct rdma_counter*,struct ib_qp*) ; 
 int /*<<< orphan*/  rdma_counter_free (struct rdma_counter*) ; 
 struct ib_qp* rdma_counter_get_qp (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_counter_res_add (struct rdma_counter*,struct ib_qp*) ; 
 scalar_t__ rdma_is_port_valid (struct ib_device*,size_t) ; 
 int /*<<< orphan*/  rdma_restrack_put (int /*<<< orphan*/ *) ; 

int rdma_counter_bind_qpn_alloc(struct ib_device *dev, u8 port,
				u32 qp_num, u32 *counter_id)
{
	struct rdma_counter *counter;
	struct ib_qp *qp;
	int ret;

	if (!rdma_is_port_valid(dev, port))
		return -EINVAL;

	if (!dev->port_data[port].port_counter.hstats)
		return -EOPNOTSUPP;

	qp = rdma_counter_get_qp(dev, qp_num);
	if (!qp)
		return -ENOENT;

	if (rdma_is_port_valid(dev, qp->port) && (qp->port != port)) {
		ret = -EINVAL;
		goto err;
	}

	counter = rdma_counter_alloc(dev, port, RDMA_COUNTER_MODE_MANUAL);
	if (!counter) {
		ret = -ENOMEM;
		goto err;
	}

	ret = rdma_counter_bind_qp_manual(counter, qp);
	if (ret)
		goto err_bind;

	if (counter_id)
		*counter_id = counter->id;

	rdma_counter_res_add(counter, qp);

	rdma_restrack_put(&qp->res);
	return ret;

err_bind:
	rdma_counter_free(counter);
err:
	rdma_restrack_put(&qp->res);
	return ret;
}