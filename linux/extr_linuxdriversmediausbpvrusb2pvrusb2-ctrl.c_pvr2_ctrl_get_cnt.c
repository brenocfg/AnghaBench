#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pvr2_ctrl {TYPE_4__* hdw; TYPE_3__* info; } ;
struct TYPE_8__ {int /*<<< orphan*/  big_lock; } ;
struct TYPE_5__ {int count; } ;
struct TYPE_6__ {TYPE_1__ type_enum; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ def; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 scalar_t__ pvr2_ctl_enum ; 

int pvr2_ctrl_get_cnt(struct pvr2_ctrl *cptr)
{
	int ret = 0;
	if (!cptr) return 0;
	LOCK_TAKE(cptr->hdw->big_lock); do {
		if (cptr->info->type == pvr2_ctl_enum) {
			ret = cptr->info->def.type_enum.count;
		}
	} while(0); LOCK_GIVE(cptr->hdw->big_lock);
	return ret;
}