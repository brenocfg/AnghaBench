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
typedef  union ib_gid {int dummy; } ib_gid ;
struct mcast_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {union ib_gid mgid; } ;
struct mcast_group {int retries; int /*<<< orphan*/  refcount; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  active_list; int /*<<< orphan*/  pending_list; int /*<<< orphan*/  pkey_index; TYPE_1__ rec; struct mcast_port* port; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCAST_INVALID_PKEY_INDEX ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mcast_group*) ; 
 struct mcast_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mcast_group* mcast_find (struct mcast_port*,union ib_gid*) ; 
 struct mcast_group* mcast_insert (struct mcast_port*,struct mcast_group*,int) ; 
 int /*<<< orphan*/  mcast_work_handler ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,union ib_gid*,int) ; 
 int /*<<< orphan*/  mgid0 ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct mcast_group *acquire_group(struct mcast_port *port,
					 union ib_gid *mgid, gfp_t gfp_mask)
{
	struct mcast_group *group, *cur_group;
	unsigned long flags;
	int is_mgid0;

	is_mgid0 = !memcmp(&mgid0, mgid, sizeof mgid0);
	if (!is_mgid0) {
		spin_lock_irqsave(&port->lock, flags);
		group = mcast_find(port, mgid);
		if (group)
			goto found;
		spin_unlock_irqrestore(&port->lock, flags);
	}

	group = kzalloc(sizeof *group, gfp_mask);
	if (!group)
		return NULL;

	group->retries = 3;
	group->port = port;
	group->rec.mgid = *mgid;
	group->pkey_index = MCAST_INVALID_PKEY_INDEX;
	INIT_LIST_HEAD(&group->pending_list);
	INIT_LIST_HEAD(&group->active_list);
	INIT_WORK(&group->work, mcast_work_handler);
	spin_lock_init(&group->lock);

	spin_lock_irqsave(&port->lock, flags);
	cur_group = mcast_insert(port, group, is_mgid0);
	if (cur_group) {
		kfree(group);
		group = cur_group;
	} else
		atomic_inc(&port->refcount);
found:
	atomic_inc(&group->refcount);
	spin_unlock_irqrestore(&port->lock, flags);
	return group;
}