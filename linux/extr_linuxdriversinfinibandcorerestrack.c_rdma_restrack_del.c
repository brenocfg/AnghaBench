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
struct rdma_restrack_entry {int valid; scalar_t__ task; int /*<<< orphan*/  node; int /*<<< orphan*/  comp; } ;
struct TYPE_2__ {int /*<<< orphan*/  rwsem; } ;
struct ib_device {TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (scalar_t__) ; 
 int /*<<< orphan*/  rdma_restrack_put (struct rdma_restrack_entry*) ; 
 struct ib_device* res_to_dev (struct rdma_restrack_entry*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void rdma_restrack_del(struct rdma_restrack_entry *res)
{
	struct ib_device *dev;

	if (!res->valid)
		return;

	dev = res_to_dev(res);
	if (!dev)
		return;

	rdma_restrack_put(res);

	wait_for_completion(&res->comp);

	down_write(&dev->res.rwsem);
	hash_del(&res->node);
	res->valid = false;
	if (res->task)
		put_task_struct(res->task);
	up_write(&dev->res.rwsem);
}