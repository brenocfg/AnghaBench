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
struct rdma_route {struct cma_work* path_rec; } ;
struct TYPE_2__ {struct rdma_route route; } ;
struct rdma_id_private {TYPE_1__ id; } ;
struct cma_work {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cma_init_resolve_route_work (struct cma_work*,struct rdma_id_private*) ; 
 int cma_query_ib_route (struct rdma_id_private*,unsigned long,struct cma_work*) ; 
 int /*<<< orphan*/  kfree (struct cma_work*) ; 
 struct cma_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct cma_work* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cma_resolve_ib_route(struct rdma_id_private *id_priv,
				unsigned long timeout_ms)
{
	struct rdma_route *route = &id_priv->id.route;
	struct cma_work *work;
	int ret;

	work = kzalloc(sizeof *work, GFP_KERNEL);
	if (!work)
		return -ENOMEM;

	cma_init_resolve_route_work(work, id_priv);

	route->path_rec = kmalloc(sizeof *route->path_rec, GFP_KERNEL);
	if (!route->path_rec) {
		ret = -ENOMEM;
		goto err1;
	}

	ret = cma_query_ib_route(id_priv, timeout_ms, work);
	if (ret)
		goto err2;

	return 0;
err2:
	kfree(route->path_rec);
	route->path_rec = NULL;
err1:
	kfree(work);
	return ret;
}