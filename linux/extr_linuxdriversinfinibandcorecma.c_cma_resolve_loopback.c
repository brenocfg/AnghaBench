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
typedef  union ib_gid {int dummy; } ib_gid ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {TYPE_1__ addr; } ;
struct TYPE_6__ {TYPE_2__ route; } ;
struct rdma_id_private {TYPE_3__ id; int /*<<< orphan*/  cma_dev; } ;
struct cma_work {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cma_bind_loopback (struct rdma_id_private*) ; 
 int /*<<< orphan*/  cma_init_resolve_addr_work (struct cma_work*,struct rdma_id_private*) ; 
 int /*<<< orphan*/  cma_wq ; 
 int /*<<< orphan*/  kfree (struct cma_work*) ; 
 struct cma_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_addr_get_sgid (int /*<<< orphan*/ *,union ib_gid*) ; 
 int /*<<< orphan*/  rdma_addr_set_dgid (int /*<<< orphan*/ *,union ib_gid*) ; 

__attribute__((used)) static int cma_resolve_loopback(struct rdma_id_private *id_priv)
{
	struct cma_work *work;
	union ib_gid gid;
	int ret;

	work = kzalloc(sizeof *work, GFP_KERNEL);
	if (!work)
		return -ENOMEM;

	if (!id_priv->cma_dev) {
		ret = cma_bind_loopback(id_priv);
		if (ret)
			goto err;
	}

	rdma_addr_get_sgid(&id_priv->id.route.addr.dev_addr, &gid);
	rdma_addr_set_dgid(&id_priv->id.route.addr.dev_addr, &gid);

	cma_init_resolve_addr_work(work, id_priv);
	queue_work(cma_wq, &work->work);
	return 0;
err:
	kfree(work);
	return ret;
}