#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rdma_restrack_root {int /*<<< orphan*/  xa; } ;
struct rdma_restrack_entry {int valid; size_t type; int /*<<< orphan*/ * task; int /*<<< orphan*/  comp; int /*<<< orphan*/  id; } ;
struct ib_device {struct rdma_restrack_root* res; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  put_task_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_restrack_put (struct rdma_restrack_entry*) ; 
 struct ib_device* res_to_dev (struct rdma_restrack_entry*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 struct rdma_restrack_entry* xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rdma_restrack_del(struct rdma_restrack_entry *res)
{
	struct rdma_restrack_entry *old;
	struct rdma_restrack_root *rt;
	struct ib_device *dev;

	if (!res->valid)
		goto out;

	dev = res_to_dev(res);
	if (WARN_ON(!dev))
		return;

	rt = &dev->res[res->type];

	old = xa_erase(&rt->xa, res->id);
	WARN_ON(old != res);
	res->valid = false;

	rdma_restrack_put(res);
	wait_for_completion(&res->comp);

out:
	if (res->task) {
		put_task_struct(res->task);
		res->task = NULL;
	}
}