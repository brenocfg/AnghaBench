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
struct rdma_restrack_entry {int valid; int /*<<< orphan*/  type; int /*<<< orphan*/  node; int /*<<< orphan*/  comp; int /*<<< orphan*/  kref; int /*<<< orphan*/ * kern_name; int /*<<< orphan*/ * task; } ;
struct TYPE_2__ {int /*<<< orphan*/  rwsem; int /*<<< orphan*/  hash; } ;
struct ib_device {TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_RESTRACK_CM_ID ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_restrack_set_task (struct rdma_restrack_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ res_is_user (struct rdma_restrack_entry*) ; 
 struct ib_device* res_to_dev (struct rdma_restrack_entry*) ; 
 int /*<<< orphan*/  set_kern_name (struct rdma_restrack_entry*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void rdma_restrack_add(struct rdma_restrack_entry *res)
{
	struct ib_device *dev = res_to_dev(res);

	if (!dev)
		return;

	if (res->type != RDMA_RESTRACK_CM_ID || !res_is_user(res))
		res->task = NULL;

	if (res_is_user(res)) {
		if (!res->task)
			rdma_restrack_set_task(res, current);
		res->kern_name = NULL;
	} else {
		set_kern_name(res);
	}

	kref_init(&res->kref);
	init_completion(&res->comp);
	res->valid = true;

	down_write(&dev->res.rwsem);
	hash_add(dev->res.hash, &res->node, res->type);
	up_write(&dev->res.rwsem);
}