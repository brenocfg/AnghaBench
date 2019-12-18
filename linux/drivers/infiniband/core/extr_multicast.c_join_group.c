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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  join_state; } ;
struct TYPE_3__ {TYPE_2__ rec; } ;
struct mcast_member {int /*<<< orphan*/  list; TYPE_1__ multicast; int /*<<< orphan*/  state; } ;
struct mcast_group {int /*<<< orphan*/  active_list; TYPE_2__ rec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCAST_MEMBER ; 
 int /*<<< orphan*/  adjust_membership (struct mcast_group*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void join_group(struct mcast_group *group, struct mcast_member *member,
		       u8 join_state)
{
	member->state = MCAST_MEMBER;
	adjust_membership(group, join_state, 1);
	group->rec.join_state |= join_state;
	member->multicast.rec = group->rec;
	member->multicast.rec.join_state = join_state;
	list_move(&member->list, &group->active_list);
}