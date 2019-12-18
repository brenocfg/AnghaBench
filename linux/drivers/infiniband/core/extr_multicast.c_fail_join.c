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
struct TYPE_2__ {int (* callback ) (int,TYPE_1__*) ;} ;
struct mcast_member {TYPE_1__ multicast; int /*<<< orphan*/  list; } ;
struct mcast_group {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (int,TYPE_1__*) ; 

__attribute__((used)) static int fail_join(struct mcast_group *group, struct mcast_member *member,
		     int status)
{
	spin_lock_irq(&group->lock);
	list_del_init(&member->list);
	spin_unlock_irq(&group->lock);
	return member->multicast.callback(status, &member->multicast);
}