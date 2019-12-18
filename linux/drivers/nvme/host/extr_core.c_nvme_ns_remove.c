#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nvme_ns {TYPE_3__* ctrl; int /*<<< orphan*/  list; TYPE_4__* disk; int /*<<< orphan*/  queue; TYPE_2__* head; int /*<<< orphan*/  siblings; int /*<<< orphan*/  fault_inject; int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  namespaces_rwsem; TYPE_1__* subsys; } ;
struct TYPE_8__ {int /*<<< orphan*/  srcu; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int GENHD_FL_UP ; 
 int /*<<< orphan*/  NVME_NS_REMOVING ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_get_integrity (TYPE_4__*) ; 
 int /*<<< orphan*/  blk_integrity_unregister (TYPE_4__*) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_4__*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_fault_inject_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_mpath_check_last_path (struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_mpath_clear_current_path (struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_put_ns (struct nvme_ns*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_ns_remove(struct nvme_ns *ns)
{
	if (test_and_set_bit(NVME_NS_REMOVING, &ns->flags))
		return;

	nvme_fault_inject_fini(&ns->fault_inject);

	mutex_lock(&ns->ctrl->subsys->lock);
	list_del_rcu(&ns->siblings);
	mutex_unlock(&ns->ctrl->subsys->lock);
	synchronize_rcu(); /* guarantee not available in head->list */
	nvme_mpath_clear_current_path(ns);
	synchronize_srcu(&ns->head->srcu); /* wait for concurrent submissions */

	if (ns->disk && ns->disk->flags & GENHD_FL_UP) {
		del_gendisk(ns->disk);
		blk_cleanup_queue(ns->queue);
		if (blk_get_integrity(ns->disk))
			blk_integrity_unregister(ns->disk);
	}

	down_write(&ns->ctrl->namespaces_rwsem);
	list_del_init(&ns->list);
	up_write(&ns->ctrl->namespaces_rwsem);

	nvme_mpath_check_last_path(ns);
	nvme_put_ns(ns);
}