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
struct TYPE_3__ {int /*<<< orphan*/  parent_sq; } ;
struct throtl_grp {TYPE_1__ service_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct throtl_grp* sq_to_tg (int /*<<< orphan*/ ) ; 
 TYPE_2__* tg_to_blkg (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_tg_can_downgrade (struct throtl_grp*) ; 

__attribute__((used)) static bool throtl_hierarchy_can_downgrade(struct throtl_grp *tg)
{
	while (true) {
		if (!throtl_tg_can_downgrade(tg))
			return false;
		tg = sq_to_tg(tg->service_queue.parent_sq);
		if (!tg || !tg_to_blkg(tg)->parent)
			break;
	}
	return true;
}