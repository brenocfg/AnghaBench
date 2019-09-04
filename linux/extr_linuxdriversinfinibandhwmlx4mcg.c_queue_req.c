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
struct mcast_req {size_t func; int /*<<< orphan*/  func_list; int /*<<< orphan*/  group_list; struct mcast_group* group; } ;
struct mcast_group {int /*<<< orphan*/  refcount; int /*<<< orphan*/  work; TYPE_2__* demux; TYPE_1__* func; int /*<<< orphan*/  pending_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  mcg_wq; } ;
struct TYPE_3__ {int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_req(struct mcast_req *req)
{
	struct mcast_group *group = req->group;

	atomic_inc(&group->refcount); /* for the request */
	atomic_inc(&group->refcount); /* for scheduling the work */
	list_add_tail(&req->group_list, &group->pending_list);
	list_add_tail(&req->func_list, &group->func[req->func].pending);
	/* calls mlx4_ib_mcg_work_handler */
	if (!queue_work(group->demux->mcg_wq, &group->work))
		safe_atomic_dec(&group->refcount);
}