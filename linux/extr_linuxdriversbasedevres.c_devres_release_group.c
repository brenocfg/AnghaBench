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
struct list_head {struct list_head* next; } ;
struct devres_group {TYPE_1__* node; } ;
struct device {int /*<<< orphan*/  devres_lock; struct list_head devres_head; } ;
struct TYPE_2__ {struct list_head entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct devres_group* find_group (struct device*,void*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int release_nodes (struct device*,struct list_head*,struct list_head*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int devres_release_group(struct device *dev, void *id)
{
	struct devres_group *grp;
	unsigned long flags;
	int cnt = 0;

	spin_lock_irqsave(&dev->devres_lock, flags);

	grp = find_group(dev, id);
	if (grp) {
		struct list_head *first = &grp->node[0].entry;
		struct list_head *end = &dev->devres_head;

		if (!list_empty(&grp->node[1].entry))
			end = grp->node[1].entry.next;

		cnt = release_nodes(dev, first, end, flags);
	} else {
		WARN_ON(1);
		spin_unlock_irqrestore(&dev->devres_lock, flags);
	}

	return cnt;
}